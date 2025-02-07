#include "pch.h"
#include "CBridge.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CBlackChain.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CDamageChain.h"
#include "CThorn.h"
#include "CPlayer.h"
#include <iostream>
using namespace std;

CBridge::CBridge()
	: m_Bridge(nullptr)
	, m_LeftOutLine(nullptr)
	, m_RightOutLine(nullptr)
{
	boss_machine_loop = CAssetMgr::GetInst()->LoadSound(L"boss_machine_loop", L"Sound\\boss_machine_loop.wav");
	if (nullptr != boss_machine_loop)
	{
		boss_machine_loop->SetVolume(20.f);
	}

}

void CBridge::SetSound()
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
	

	boss_machine_loop = CAssetMgr::GetInst()->LoadSound(L"boss_machine_loop", L"Sound\\boss_machine_loop.wav");
	if (nullptr != boss_machine_loop)
	{
		boss_machine_loop->SetVolume(a);
	}


}

CBridge::~CBridge()
{
}


void CBridge::Begin()
{

}

void CBridge::Tick()
{
	SetSound();
	if (!LoopSoundPlay && MoveBirdge) {
		boss_machine_loop->Play();
		LoopSoundPlay = true;
	}
	cout << 1 << endl;
	float totalTime = 20.0f;       // 총 이동 시간
	float totalDistance = 1000.0f;  // 총 이동 거리
	float moveSpeed = totalDistance / totalTime; // 초당 이동할 거리 (5 px/sec)
	
	if (MoveBirdge && elapsedTime < totalTime) {
		elapsedTime += DT; // deltaTime은 프레임 간 경과 시간
		float frameMove = moveSpeed * DT; // 이번 프레임에 이동할 거리
		cout << frameMove << endl;
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecChain = pCurLevel->GetObjects(LAYER_TYPE::CHAIN);
		const vector<CObj*>& vecDamageChain = pCurLevel->GetObjects(LAYER_TYPE::DAMAGE_CHAIN);
		const vector<CObj*>& vecThorn = pCurLevel->GetObjects(LAYER_TYPE::THORN);
		const vector<CObj*>& vecBirdge = pCurLevel->GetObjects(LAYER_TYPE::BRIDGE);
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);


		// 체인 이동
		for (int i = 0; i < vecChain.size(); i++) {
			CBlackChain* chain = dynamic_cast<CBlackChain*>(vecChain[i]);
			Vec2 CurChainpos = chain->GetPos();
			chain->SetPos(CurChainpos.x, CurChainpos.y - frameMove); // 체인 위로 이동
		}
		//for (int i = vecChain.size() - 1; i > 0 ; i--) {
		//	CBlackChain* chain = dynamic_cast<CBlackChain*>(vecChain[i]);
		//	Vec2 CurChainpos = chain->GetPos();
		//	chain->SetPos(CurChainpos.x, CurChainpos.y - frameMove); // 체인 위로 이동
		//}
		// 데미지체인 이동
		for (int i = 0; i < vecDamageChain.size(); i++) {
			CDamageChain* chain = dynamic_cast<CDamageChain*>(vecDamageChain[i]);
			Vec2 CurChainpos = chain->GetPos();
			chain->SetPos(CurChainpos.x, CurChainpos.y - frameMove); // 체인 위로 이동
		}
		//다리 이동
		for (int i = 0; i < vecBirdge.size(); i++) {
			CBridge* pBridge = dynamic_cast<CBridge*>(vecBirdge[i]);
			Vec2 CurBridgepos = pBridge->GetPos();
			pBridge->SetPos(CurBridgepos.x, CurBridgepos.y - frameMove); // 체인 위로 이동
		}
		//플레이어 이동
		for (int i = 0; i < vecPlayer.size(); i++) {
			vecPlayer[i]->SetPos(vecPlayer[i]->GetPos().x, vecPlayer[i]->GetPos().y - frameMove);
		}
		//가시 이동
		for (int i = 0; i < vecThorn.size(); i++) {
			CThorn* pBridge = dynamic_cast<CThorn*>(vecThorn[i]);
			Vec2 CurBridgepos = pBridge->GetPos();
			pBridge->SetPos(CurBridgepos.x, CurBridgepos.y - frameMove); // 체인 위로 이동
		}

		// 위로 사라진 체인을 아래로 재배치하여 재활용
		for (int i = 0; i < vecChain.size(); i++) {
			CBlackChain* chain = dynamic_cast<CBlackChain*>(vecChain[i]);
			Vec2 CurChainpos = chain->GetPos();

			if (CurChainpos.y < -100.f) {
				chain->SetPos(CurChainpos.x, 900.f); // 체인을 초기 위치로 이동하여 재활용
			}
		}

		//가시 재활용
		for (int i = 0; i < vecThorn.size(); i++) {
			CThorn* chain = dynamic_cast<CThorn*>(vecThorn[i]);
			Vec2 CurChainpos = chain->GetPos();

			if (CurChainpos.y < 150.f) {
				chain->SetPos(CurChainpos.x, 350.f); // 체인을 초기 위치로 이동하여 재활용
				chain->BOSS_CHECK = true;
			}
			else if (CurChainpos.y < 900.f && CurChainpos.y > 650.f) {
				chain->SetPos(CurChainpos.x, 1070.f); // 체인을 초기 위치로 이동하여 재활용
				chain->BOSS_CHECK = true;
			}
		}

		// 위로 사라진 다리 아래로 재배치하여 재활용
		for (int i = 0; i < vecBirdge.size(); i++) {
			CBridge* pBridge = dynamic_cast<CBridge*>(vecBirdge[i]);
			Vec2 CurBridgepos = pBridge->GetPos();
			if (CurBridgepos.y < -800.f) {
				pBridge->SetPos(CurBridgepos.x, 1000.f);
			}
		}

	}
	else {
		LoopSoundPlay = false;
		elapsedTime = 0.0f;
	}
}

void CBridge::Render()
{

	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};

	swprintf_s(filePath, 100, L"Texture\\bridgeInner.png");
	swprintf_s(textureName, 100, L"bridgeInner");
	CTexture* m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	swprintf_s(filePath, 100, L"Texture\\bridgeOuter.png");
	swprintf_s(textureName, 100, L"bridgeOuter");
	CTexture* m_LeftOutLine = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	swprintf_s(filePath, 100, L"Texture\\bridgeOuterRIGHT.png");
	swprintf_s(textureName, 100, L"bridgeOuterRIGHT");
	CTexture* m_RightOutLine = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(dc
		, (vPos.x - (m_Bridge->GetWidth()) / 2.f) + x_offset - 18.f
		, vPos.y
		, m_Bridge->GetWidth()
		, m_Bridge->GetHeight()
		, m_Bridge->GetDC()
		, 0, 0
		, m_Bridge->GetWidth()
		, m_Bridge->GetHeight()
		, blend);

	AlphaBlend(dc
		, (vPos.x - (m_LeftOutLine->GetWidth()) / 2.f) - 424.f - 18.f
		, vPos.y
		, m_LeftOutLine->GetWidth()
		, m_LeftOutLine->GetHeight()
		, m_LeftOutLine->GetDC()
		, 0, 0
		, m_LeftOutLine->GetWidth()
		, m_LeftOutLine->GetHeight()
		, blend);

	AlphaBlend(dc
		, (vPos.x - (m_RightOutLine->GetWidth()) / 2.f) + 424.f - 18.f
		, vPos.y
		, m_RightOutLine->GetWidth()
		, m_RightOutLine->GetHeight()
		, m_RightOutLine->GetDC()
		, 0, 0
		, m_RightOutLine->GetWidth()
		, m_RightOutLine->GetHeight()
		, blend);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);

}