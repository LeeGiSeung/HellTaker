#include "pch.h"
#include "CKeybox.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFSM.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CFlipbookPlayer.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CSound.h"
#include "CPlayer.h"

enum KEY_BOX_STATE {
	GET_KEY_VFX
};

CKeybox::CKeybox()
	: m_Tex(nullptr)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, KeyBoxSound(nullptr)
	, m_Collider(nullptr)
	, openbox(false)
{

	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(100.f, 100.f));

	CreateKeyBoxFlipbook();

	KeyBoxSound = CAssetMgr::GetInst()->LoadSound(L"KeyBoxSound", L"Sound\\door_opening_01.wav");
	if (nullptr != KeyBoxSound)
	{
		KeyBoxSound->SetVolume(20.f);
	}

}

void CKeybox::SetSound()
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

	if (nullptr != KeyBoxSound)
	{
		KeyBoxSound->SetVolume(a);
	}
}

CKeybox::~CKeybox()
{
}


void CKeybox::CreateKeyBoxFlipbook()
{
	//CreatePngFlipbook(L"GET_KEY_VFX", L"GetKeyVFX", 9);

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(GET_KEY_VFX, CAssetMgr::GetInst()->LoadFlipbook(L"GET_KEY_VFX", L"Flipbook\\GET_KEY_VFX.flip"));

}

void CKeybox::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite �����ϱ�
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// �� �����ӿ� ���� ��� ����
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"assets100V%d", i);*/
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

void CKeybox::Begin()
{
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};
	// �� �����ӿ� ���� ��� ����
	swprintf_s(filePath, 100, L"Texture\\backup_lockbox.png");
	swprintf_s(textureName, 100, L"backup_lockbox");

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	m_Tex = pAtlas;

	m_FlipbookPlayer->Play(GET_KEY_VFX, 15.f, false);
}

void CKeybox::Tick()
{
	SetSound();

	if (openbox) {
		DeleteObject(this);
	}

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	float m_DetectRange = 10.f;
	CPlayer* cp = dynamic_cast<CPlayer*>(vecMon[0]);


	Vec2 vPos = GetRenderPos();
	Vec2 vMonPos = cp->GetPos(); // ������ ��ġ

	float Dist = (vPos - vMonPos).Length();

	// �ּҰŸ��� ���ŵ� ���
	if (Dist < m_DetectRange && !openbox && cp->KeyBox_Key)
	{
		KeyBoxSound->Play();
		openbox = true;
		//�÷��̾� Key ���� ��ȯ
	}
}

void CKeybox::Render()
{

	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	int a = m_Tex->GetWidth();
	int b = m_Tex->GetHeight();
	float c = vPos.x + m_Tex->GetWidth() / 2.f;
	float d = vPos.y + m_Tex->GetHeight() / 2.f;

	AlphaBlend(dc
		, (vPos.x - (m_Tex->GetWidth()) / 2.f) + x_offset
		, (vPos.y - (m_Tex->GetHeight()) / 2.f) + 30.f + y_offset
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0, 0
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, blend);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
}

