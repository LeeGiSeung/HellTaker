#include "pch.h"
#include "CRestartCutScene.h"
#include "define.h"

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
	TRANSITION
};

CRestartCutScene::CRestartCutScene()
	:
	ReStartCutSceneEnd(false),
	m_FlipbookPlayer(nullptr),
	pTransSound(nullptr),
	cp(nullptr)

{
	CreatePlayerFlipbook();
	Screen_Changer = CAssetMgr::GetInst()->LoadSound(L"Screen_Changer", L"Sound\\screen_changer_part1_01.wav");
	if (nullptr != Screen_Changer)
	{
		Screen_Changer->SetVolume(20.f);
	}
	SetSound();
}

void CRestartCutScene::SetSound()
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
	Screen_Changer->SetVolume(a);
	Screen_Changer->Play();
}

CRestartCutScene::~CRestartCutScene()
{

}

void CRestartCutScene::Begin()
{
	m_FlipbookPlayer->Play(TRANSITION, 25.f, false);

}

void CRestartCutScene::Tick()
{
	if (m_FlipbookPlayer->IsFinish()) {

		DeleteObject(this);

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

		//if (cp->CurLevel == STAGE_8) {
		//	ChangeLevel(LEVEL_TYPE::BOSS_0);
		//}

		cp->PlayerMove_Count = cp->Init_PlayerMove_Count;
		cp->RestartCutsceneEnd = true;
		//PlayerMove_Count = Init_PlayerMove_Count;
		//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		//const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		//vecMon[0]->SetPos(vecMon[0]->GetStartPos());

	}
}

void CRestartCutScene::Render()
{
	m_FlipbookPlayer->FullRender();
}

void CRestartCutScene::play()
{

}

void CRestartCutScene::CreatePlayerFlipbook()
{
	//CreatePngFlipbook(L"TRANSITION", L"transition", 29);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(TRANSITION, CAssetMgr::GetInst()->LoadFlipbook(L"TRANSITION", L"Flipbook\\TRANSITION.flip"));
}

void CRestartCutScene::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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
