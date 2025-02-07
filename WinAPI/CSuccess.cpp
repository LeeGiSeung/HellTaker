#include "pch.h"
#include "CSuccess.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CFlipbookPlayer.h"
#include "CSound.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CSound.h"
#include "CLevel.h"
#include "CLevelMgr.h"

#include "CPlayer.h"
#include "CLevel_Start.h"

enum PlayCut {
	SUCCESS,
	J_SUCCESS
};

CSuccess::CSuccess():
	SuccessEnd(false),
	m_FlipbookPlayer(nullptr),
	SUCCESS_Sound(nullptr),
	cp(nullptr)
{
	CreatePlayerFlipbook();

	NewFunction();

}

void CSuccess::NewFunction()
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

	CSound* SUCCESS_Sound = CAssetMgr::GetInst()->LoadSound(L"SUCCESS_Sound", L"Sound\\dialogue_success_01.wav");
	if (nullptr != SUCCESS_Sound)
	{
		SUCCESS_Sound->SetVolume(a);
		SUCCESS_Sound->Play();
	}
	if (cp->CurLevel == LEVEL_CHECK::BOSS_0) {
		m_FlipbookPlayer->Play(J_SUCCESS, 10.f, false);
	}
	else {
		m_FlipbookPlayer->Play(SUCCESS, 10.f, false);
	}
}

CSuccess::~CSuccess()
{

}

void CSuccess::CreatePlayerFlipbook()
{

	//CreatePngFlipbook(L"SUCCESS", L"success", 8);
	//CreatePngFlipbook(L"J_SUCCESS", L"j_success", 8);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(SUCCESS, CAssetMgr::GetInst()->LoadFlipbook(L"SUCCESS", L"Flipbook\\SUCCESS.flip"));
	m_FlipbookPlayer->AddFlipbook(J_SUCCESS, CAssetMgr::GetInst()->LoadFlipbook(L"J_SUCCESS", L"Flipbook\\J_SUCCESS.flip"));
}

void CSuccess::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"transition%d", i);*/
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

void CSuccess::Begin()
{
	//m_FlipbookPlayer->Play(SUCCESS, 20.f, false);
}

void CSuccess::Tick()
{
	if (m_FlipbookPlayer->IsFinish()) {
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

		cp->SuccessEnd = true;
	}
}

void CSuccess::Render()
{
	Vec2 x;

	x.x = 950.f;
	x.y = 951.f;
	m_FlipbookPlayer->CenterRender(450.f);
}

