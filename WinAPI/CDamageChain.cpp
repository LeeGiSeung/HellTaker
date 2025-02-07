#include "pch.h"
#include "CDamageChain.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CBlackChain.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CFlipbookPlayer.h"
#include "CCamera.h"

CDamageChain::CDamageChain()
	:m_Collider(nullptr)
	, m_FlipbookChainPlayer(nullptr)
{

	ChainBlink_1 = CAssetMgr::GetInst()->LoadSound(L"ChainBlink_1", L"Sound\\boss_chain_blink_01.wav");
	if (nullptr != ChainBlink_1)
	{
		ChainBlink_1->SetVolume(20.f);
	}

	ChainBlink_2 = CAssetMgr::GetInst()->LoadSound(L"ChainBlink_1", L"Sound\\boss_chain_blink_02.wav");
	if (nullptr != ChainBlink_2)
	{
		ChainBlink_2->SetVolume(20.f);
	}

	ChainBlink_3 = CAssetMgr::GetInst()->LoadSound(L"ChainBlink_3", L"Sound\\boss_chain_blink_03.wav");
	if (nullptr != ChainBlink_3)
	{
		ChainBlink_3->SetVolume(20.f);
	}

	ChainBlink_4 = CAssetMgr::GetInst()->LoadSound(L"ChainBlink_4", L"Sound\\boss_chain_blink_04.wav");
	if (nullptr != ChainBlink_4)
	{
		ChainBlink_4->SetVolume(20.f);
	}

	pPlayer_damage = CAssetMgr::GetInst()->LoadSound(L"pPlayer_damage", L"Sound\\boss_chain_damage_03.wav");
	if (nullptr != pPlayer_damage)
	{
		pPlayer_damage->SetVolume(20.f);
	}

	CreatePlayerFlipbook();

}

void CDamageChain::SetSound()
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

	if (nullptr != ChainBlink_1)
	{
		ChainBlink_1->SetVolume(a);
	}

	if (nullptr != ChainBlink_2)
	{
		ChainBlink_2->SetVolume(a);
	}

	if (nullptr != ChainBlink_3)
	{
		ChainBlink_3->SetVolume(a);
	}

	if (nullptr != ChainBlink_4)
	{
		ChainBlink_4->SetVolume(a);
	}

	if (nullptr != pPlayer_damage)
	{
		pPlayer_damage->SetVolume(a);
	}
}

void CDamageChain::CreatePlayerFlipbook()
{
	//CreatePngFlipbook(L"HUGE_VFX_1", L"huge_vfx1", 6);
	m_FlipbookChainPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookChainPlayer->AddFlipbook(HUGE_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"HUGE_VFX_1", L"Flipbook\\HUGE_VFX_1.flip"));

}

void CDamageChain::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
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

CDamageChain::~CDamageChain()
{
}

void CDamageChain::Begin()
{
	if (Chaindir == 0) {
		m_Collider = (CCollider*)AddComponent(new CCollider);
		m_Collider->SetScale(Vec2(2500.f, 55.f));
	}
	else {
		m_Collider = (CCollider*)AddComponent(new CCollider);
		m_Collider->SetScale(Vec2(55.f, 2500.f));
	}

	m_FlipbookChainPlayer->Play(HUGE_VFX_1, 10.f, false);
}

void CDamageChain::Tick()
{
	SetSound();

	if (DeleteChain) {
		DeleteObject(this);
	}
	if (HitChain) {
		CCamera::GetInst()->Oscillation(1, 10, 10);
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);
		cp->PlayHugeVFX();
		cp->JudmentPlayerHealth -= 1;
	}
	if (ChainSound) {
		if (SelectChainBlick == 1) {
			ChainBlink_1->Play();
		}
		else if (SelectChainBlick == 2) {
			ChainBlink_2->Play();
		}
		else if (SelectChainBlick == 3) {
			ChainBlink_3->Play();
		}
		else if (SelectChainBlick == 4) {
			ChainBlink_4->Play();
		}
	}
}

struct CHAIN_STEP {
	float HeightScale;
	float Saturation;
	bool CanHit;
};

void CDamageChain::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};

	if (Chaindir == 0) {
		wchar_t filePath[100] = L"Texture\\WhiteAttackChain90.png";
		wchar_t textureName[100] = L"WhiteAttackChain90";
		CTexture* m_DamageChain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		if (!m_DamageChain) {
			return; // 텍스처 로드 실패 시 함수 종료
		}

		Vec2 vPos = GetRenderPos();

		animationProgress += DT * (2 * 3.14159265f) / 0.5f; // 0.8초 동안 주기를 완성

		// cos 함수로 크기 변화 범위를 0.1 ~ 0.5로 제한하고 커지게 수정
		float scaleFactor = fmax(0.1f, fmin(0.5f, 0.3f * cos(animationProgress) + 0.3f));
		int height = static_cast<int>(m_DamageChain->GetHeight() * scaleFactor);

		// 중심 위치를 유지하기 위한 y 좌표 보정
		float yPosAdjusted = (vPos.y - height) / 2.f + vPos.y / 2.f;

		// 주기적인 투명도 변화를 위한 알파 값 조정
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = static_cast<BYTE>(128 + 127 * cos(animationProgress));
		blend.AlphaFormat = AC_SRC_ALPHA;

		// AlphaBlend 호출로 연출 적용
		AlphaBlend(dc,
			vPos.x - (m_DamageChain->GetWidth() / 2.f) - 200.f,
			yPosAdjusted,
			m_DamageChain->GetWidth() * 2.5f,
			height,
			m_DamageChain->GetDC(),
			0, 0,
			m_DamageChain->GetWidth(),
			m_DamageChain->GetHeight(),
			blend);

		// 주기가 끝나면 애니메이션을 재설정
		if (animationProgress >= 2 * 3.14159265f && !ChainSound) {
			ChainSound = true;
			DeleteChain = true;
			//DeleteObject(this);
		}
	}
	else if (Chaindir == 1) {
		wchar_t filePath[100] = L"Texture\\WhiteAttackChain.png";
		wchar_t textureName[100] = L"WhiteAttackChain";
		CTexture* m_DamageChain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		if (!m_DamageChain) {
			return; // 텍스처 로드 실패 시 함수 종료
		}

		Vec2 vPos = GetRenderPos();

		animationProgress += DT * (2 * 3.14159265f) / 0.5f; // 0.8초 동안 주기를 완성

		// cos 함수로 크기 변화 범위를 0.1 ~ 0.5로 제한하고 커지게 수정
		float scaleFactor = fmax(0.1f, fmin(0.5f, 0.3f * cos(animationProgress) + 0.3f));
		int Width = static_cast<int>(m_DamageChain->GetWidth() * scaleFactor);

		// 중심 위치를 유지하기 위한 x 좌표 보정
		float xPosAdjusted = (vPos.x - Width) / 2.f + vPos.x / 2.f;

		// 주기적인 투명도 변화를 위한 알파 값 조정
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = static_cast<BYTE>(128 + 127 * cos(animationProgress));
		blend.AlphaFormat = AC_SRC_ALPHA;

		// AlphaBlend 호출로 연출 적용
		AlphaBlend(dc,
			xPosAdjusted,
			vPos.y - (m_DamageChain->GetHeight() / 2.f) - 200.f,
			Width,
			m_DamageChain->GetHeight() * 2.5f,
			m_DamageChain->GetDC(),
			0, 0,
			m_DamageChain->GetWidth(),
			m_DamageChain->GetHeight(),
			blend);

		// 주기가 끝나면 애니메이션을 재설정
		if (animationProgress >= 2 * 3.14159265f && !ChainSound) {
			ChainSound = true;
			DeleteChain = true;
			//DeleteObject(this);
		}
	}
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}


void CDamageChain::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player") {
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

		if (cp->GodMode == false) {
			if (DeleteChain) {
				pPlayer_damage->Play();
				HitChain = true;
				cp->DamageChain = true;
			}
		}
	}
}

