#include "pch.h"
#include "CKey.h"

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

enum KEY_STAGE {
	KEY_IDLE,
	GET_KEY_VFX
};

CKey::CKey()
	: m_FlipbookPlayer(nullptr)
	, m_Collider(nullptr)
	, KeyPickUpSound(nullptr)
	, GetKey(false)
{
	KeyPickUpSound = CAssetMgr::GetInst()->LoadSound(L"KeyPickUpSound", L"Sound\\key_pick_up_01.wav");
	if (nullptr != KeyPickUpSound)
	{
		KeyPickUpSound->SetVolume(20.f);
	}

	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(100.f, 100.f));

	CreateMonsterFlipbook();

}

void CKey::SetSound()
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

	if (nullptr != KeyPickUpSound)
	{
		KeyPickUpSound->SetVolume(a);
	}
}

CKey::~CKey()
{
}

void CKey::CreateMonsterFlipbook()
{
	//CreatePngFlipbook(L"KEY_IDLE", L"Key", 12);
	//CreatePngFlipbook(L"GET_KEY_VFX", L"GetKeyVFX", 9);

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(KEY_IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"KEY_IDLE", L"Flipbook\\KEY_IDLE.flip"));
	m_FlipbookPlayer->AddFlipbook(GET_KEY_VFX, CAssetMgr::GetInst()->LoadFlipbook(L"GET_KEY_VFX", L"Flipbook\\GET_KEY_VFX.flip"));

}

void CKey::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"assets100V%d", i);*/
		swprintf_s(textureName, 100, L"%s_%d", _Pngname.c_str(), i);

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		CSprite* pSprite = new CSprite;

		// _RightBot를 그대로 넘기지 않고 크기로 사용해야 합니다.
		int a = pAtlas->GetWidth();
		int b = pAtlas->GetHeight();
		int c = 0;

		Vec2 spriteSize = Vec2(static_cast<float>(pAtlas->GetWidth()), static_cast<float>(pAtlas->GetHeight()));
		Vec2 spritePosition = Vec2(0.0f, 0.0f); // 원하는 위치로 설정, 예를 들어 (0,0)
		pSprite->Create(pAtlas, spritePosition, spriteSize);

		// Key를 만들 때, wstring을 미리 생성 후 사용
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, L"%s_%d", _FlipbookName.c_str(), i);  // 여기서 형식 문자열을 분리하여 사용
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

	// Flipbook 생성하기
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

void CKey::Begin()
{
	m_FlipbookPlayer->Play(KEY_IDLE, 15.f, true);
}

void CKey::Tick()
{
	SetSound();

	if (m_FlipbookPlayer->IsFinish() && GetKey) {
		DeleteObject(this);
	}

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	float m_DetectRange = 10.f;
	CPlayer* cp = dynamic_cast<CPlayer*>(vecMon[0]);


	Vec2 vPos = GetRenderPos();
	Vec2 vMonPos = cp->GetPos(); // 몬스터의 위치

	float Dist = (vPos - vMonPos).Length();

	// 최소거리가 갱신된 경우
	if (Dist < m_DetectRange && !GetKey)
	{
		KeyPickUpSound->Play();
		m_FlipbookPlayer->Play(GET_KEY_VFX, 15.f, false);
		GetKey = true;

		//플레이어 Key 상태 변환
		cp->KeyBox_Key = true;
	}

}

void CKey::Render()
{
	m_FlipbookPlayer->Render(y_offset, x_offset);
}

void CKey::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		
	}
}


