#include "pch.h"
#include "CBrakeChain.h"
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
#include "CAssetMgr.h"

CBrakeChain::CBrakeChain()
{
	SetSound();
}

void CBrakeChain::SetSound()
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

	boss_big_chain_show_01 = CAssetMgr::GetInst()->LoadSound(L"boss_big_chain_show_01", L"Sound\\boss_big_chain_show_01.wav");
	if (nullptr != boss_big_chain_show_01)
	{
		boss_big_chain_show_01->SetVolume(a);
	}
	boss_big_chain_show_02 = CAssetMgr::GetInst()->LoadSound(L"boss_big_chain_show_02", L"Sound\\boss_big_chain_show_02.wav");
	if (nullptr != boss_big_chain_show_02)
	{
		boss_big_chain_show_02->SetVolume(a);
	}
}

CBrakeChain::~CBrakeChain()
{
}

void CBrakeChain::Begin()
{
	if (dir == 0) {
		boss_big_chain_show_01->Play();
	}
	else {
		boss_big_chain_show_02->Play();
	}
}

void CBrakeChain::Tick()
{
	if (hp == 0) {
		DeleteObject(this);
	}
	if (!alphaincr) {
		alpha -= 1;
	}
	else if (alphaincr) {
		alpha += 1;
	}
	if (alpha == 255) {
		alphaincr = false;
	}
	else if (alpha == 100) {
		alphaincr = true;
	}
}

void CBrakeChain::Render()
{

	HDC dc = CEngine::GetInst()->GetSecondDC();

	if (dir == 0) {
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\chain25angleLeft.png");
		swprintf_s(textureName, 100, L"chain25angleLeft");

		m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	}

	else if (dir == 1) {
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\chain25angleRIGHT.png");
		swprintf_s(textureName, 100, L"chain25angleRIGHT");
		m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	}

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = alpha;
	blend.AlphaFormat = AC_SRC_ALPHA;
	
	int a = m_Tex->GetHeight();

	AlphaBlend(dc
		, (vPos.x - (m_Tex->GetWidth()) / 2.f) + x_offset
		, (vPos.y - (m_Tex->GetHeight()) / 2.f) + y_offset
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0, 0
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, blend);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}
