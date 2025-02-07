#include "pch.h"
#include "CDeathP.h"

#include "define.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CFlipbookPlayer.h"
#include "CSound.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CSound.h"
#include "CRestartCutScene.h"
#include "CEngine.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CCamera.h"

class CFlipbookPlayer;
class CSound;

enum PlayCut {
	DEATH
};

CDeathP::CDeathP()
	:
	CDeathEnd(false),
	m_FlipbookPlayer(nullptr),
	pTransSound(nullptr)
{
	CreatePlayerFlipbook();

	SetSound();
}

void CDeathP::SetSound()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	float a = 40.f;

	if (cp->SoundIndex == 0) {
		a = 50.f;
	}
	else if (cp->SoundIndex == 1) {
		a = 30.f;
	}
	else if (cp->SoundIndex == 2) {
		a = 10.f;
	}

	CSound* Death_Sound = CAssetMgr::GetInst()->LoadSound(L"Death_Sound", L"Sound\\player_death_01.wav");
	if (nullptr != Death_Sound)
	{
		Death_Sound->SetVolume(a);
		Death_Sound->Play();
	}
}

CDeathP::~CDeathP()
{
}

void CDeathP::Begin()
{
	m_FlipbookPlayer->Play(DEATH, 20.f, false);
	CCamera::GetInst()->Oscillation(1, 8, 10);
}

void CDeathP::Tick()
{

	if (m_FlipbookPlayer->m_SpriteIdx == 10 && !CDeathEnd) {
		CRestartCutScene* pResetCutScene = new CRestartCutScene;
		//pResetCutScene->SetScale(100.f, 100.f);

		CreateObject(pResetCutScene, LAYER_TYPE::CUTSCENE);
		CDeathEnd = true;
	}

	if (m_FlipbookPlayer->IsFinish()) {
		//SetPos(GetStartPos());
		DeleteObject(this);
		//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		//const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		//vecMon[0]->SetPos(vecMon[0]->GetStartPos());

	}
}

void CDeathP::Render()
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HBRUSH hBrush = CreateSolidBrush(RGB(2, 2, 27));
	HDC dc = CEngine::GetInst()->GetSecondDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	Rectangle(dc
		, 0, vResolution.y - 1080.f
		, GetRenderPos().x + 1920.f
		, GetRenderPos().y + 1080.f);

	SelectObject(dc, hPrevBrush);
	SelectObject(dc, hBrush);
	DeleteObject(hBrush);
	DeleteObject(hPrevBrush);

	m_FlipbookPlayer->Render(-250.f);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}


void CDeathP::CreatePlayerFlipbook()
{
	//death_P_0
	//CreatePngFlipbook(L"DEATH", L"death_P", 18);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"DEATH", L"Flipbook\\DEATH.flip"));
}

void CDeathP::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite �����ϱ�
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// �� �����ӿ� ���� ��� ����
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"death_P%d", i);*/
		swprintf_s(textureName, 100, L"%s_%d", _Pngname.c_str(), i);

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		CSprite* pSprite = new CSprite;

		// _RightBot�� �״�� �ѱ��� �ʰ� ũ��� ����ؾ� �մϴ�.
		int a = pAtlas->GetWidth();
		int b = pAtlas->GetHeight();
		int c = 0;

		Vec2 spriteSize = Vec2(static_cast<float>(pAtlas->GetWidth()), static_cast<float>(pAtlas->GetHeight()));
		Vec2 spritePosition = Vec2(0.0f, 0.0f); // ���ϴ� ��ġ�� ����, ���� ��� (0,0)
		pSprite->Create(pAtlas, spritePosition, spriteSize);

		// Key�� ���� ��, wstring�� �̸� ���� �� ���
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, L"%s_%d", _FlipbookName.c_str(), i);  // ���⼭ ���� ���ڿ��� �и��Ͽ� ���

		CAssetMgr::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}


	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		wstring Path = L"Sprite\\";
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}

	// Flipbook �����ϱ�
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	wstring Path = L"Flipbook\\";
	pFlipbook->Save(Path + _FlipbookName);
}
