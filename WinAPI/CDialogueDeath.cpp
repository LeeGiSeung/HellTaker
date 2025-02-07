#include "pch.h"
#include "CDialogueDeath.h"

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

class CFlipbookPlayer;
class CSound;

CDialogueDeath::CDialogueDeath()
	:
	CDeathEnd(false),
	m_FlipbookPlayer(nullptr),
	pTransSound(nullptr)
{
	CreatePlayerFlipbook();

	SetSound();
}

void CDialogueDeath::SetSound()
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

	CSound* DiaDeath_Sound = CAssetMgr::GetInst()->LoadSound(L"DiaDeath_Sound", L"Sound\\bad_end_screen_01.wav");
	if (nullptr != DiaDeath_Sound)
	{
		DiaDeath_Sound->SetVolume(a);
		DiaDeath_Sound->Play();
	}
}

CDialogueDeath::~CDialogueDeath()
{
}

void CDialogueDeath::Begin()
{
	m_FlipbookPlayer->Play(PLAYER_DEATH_CUTSCENE_FLIPBOOK, 10.f, false);
}

void CDialogueDeath::Tick()
{


	if (m_FlipbookPlayer->IsFinish() && KEY_TAP(ENTER)) {
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecMon[0]);
		if (cp->CurLevel == LEVEL_CHECK::STAGE_8) {
			ChangeLevel(LEVEL_TYPE::BOSS_0);
		}
		else {
			vecMon[0]->SetPos(vecMon[0]->GetStartPos());
			CRestartCutScene* pResetCutScene = new CRestartCutScene;
			CreateObject(pResetCutScene, LAYER_TYPE::CUTSCENE);
			DeleteObject(this);
		}
	}
}

void CDialogueDeath::Render()
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
		, GetRenderPos().y + 3000.f);

	SelectObject(dc, hBrush);
	SelectObject(dc, hPrevBrush);
	DeleteObject(hPrevBrush);
	DeleteObject(hBrush);

	DrawDieMessage(dc, vResolution);

	Vec2 x;
	x.x = 1920.f / 2.f;
	x.y = 1080.f / 2.f - 200.f;

	m_FlipbookPlayer->Inplace_Render(x);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	DeleteObject(hPrevBrush);
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}

void CDialogueDeath::DrawDieMessage(HDC dc, Vec2& vResolution)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	std::wstring text = cp->diemessage;


	HFONT hFont = CreateFont(
		40,                    // ���� ����
		0,                     // ���� �� (0���� �ڵ� ����)
		0,                     // ���� ����
		0,                     // ���� ���� ����
		FW_BOLD,			   // ���� �β�
		FALSE,                 // ����� ����
		FALSE,                 // ���� ����
		FALSE,                 // ��Ҽ� ����
		ANSI_CHARSET,          // ���� ����
		OUT_DEFAULT_PRECIS,    // ��� ���е�
		CLIP_DEFAULT_PRECIS,   // Ŭ���� ���е�
		DEFAULT_QUALITY,       // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS, // �۲� ������ �� �۲� �йи�
		L"CrimsonPro-Medium"   // �۲� �̸�
	);

	SetTextColor(dc, RGB(175, 31, 16));
	SetBkMode(dc, TRANSPARENT);
	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	float hg = 600.f;
	SIZE textSize;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	float textPosX = (vResolution.x - textSize.cx) / 2; // ���� �߾� ����
	float textPosY = vResolution.y / 2.f + 50.f;
	TextOut(
		dc,
		textPosX,
		textPosY + 60.f,
		text.c_str(),
		text.length()
	);

	text = cp->diemessage2;

	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);

	textPosX = (vResolution.x - textSize.cx) / 2; // ���� �߾� ����

	TextOut(
		dc,
		textPosX,
		textPosY + 100.f,
		text.c_str(),
		text.length()
	);

	DeleteObject(hFont);
	DeleteObject(hOldFont);
}


void CDialogueDeath::CreatePlayerFlipbook()
{
	//CreatePngFlipbook(L"PLAYER_DEATH_CUTSCENE_FLIPBOOK", L"dialogueDeathExport", 9);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(PLAYER_DEATH_CUTSCENE_FLIPBOOK, CAssetMgr::GetInst()->LoadFlipbook(L"PLAYER_DEATH_CUTSCENE_FLIPBOOK", L"Flipbook\\PLAYER_DEATH_CUTSCENE_FLIPBOOK.flip"));
}

void CDialogueDeath::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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
