#include "pch.h"
#include "CJudmentPiston.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include <iostream>

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CFlipbookPlayer.h"
#include "CSprite.h"
#include "CBlackChain.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CTimeMgr.h"
#include "CBridge.h"
#include "CSound.h"

using namespace std;

enum PISTON
{
	PISTON,
	NULL_PISTON
};

enum GEAR_STATE
{
	PISTON_RUN,
	PISTON_STOP
};

CJudmentPiston::CJudmentPiston()
	: m_FlipbookPlayer(nullptr)
	, TurnPiston(false)
{
	CreateFireFlipbook();
}

CJudmentPiston::~CJudmentPiston()
{

}


void CJudmentPiston::Begin()
{
	if (Under) {
		m_FlipbookPlayer->Play(PISTON, 10.f, true);
	}
	else {
		m_FlipbookPlayer->Play(NULL_PISTON, 10.f, true);
	}
	
}

void CJudmentPiston::Tick()
{

}

void CJudmentPiston::Render()
{

	HDC dc = CEngine::GetInst()->GetSecondDC();

	if (TurnPiston) {
		m_FlipbookPlayer->Render();
	}
	else {
		if (Under) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\sinPiston_0.png");
			swprintf_s(textureName, 100, L"sinPiston_0");
			CTexture* m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);


			Vec2 vPos = GetRenderPos();
			Vec2 vScale = GetScale();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(dc
				, (vPos.x - (m_Bridge->GetWidth()) / 2.f) + x_offset
				, (vPos.y - (m_Bridge->GetHeight()) / 2.f) + y_offset
				, m_Bridge->GetWidth()
				, m_Bridge->GetHeight()
				, m_Bridge->GetDC()
				, 0, 0
				, m_Bridge->GetWidth()
				, m_Bridge->GetHeight()
				, blend);
		}
		else {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\sinPistonNull_0.png");
			swprintf_s(textureName, 100, L"sinPistonNull_0");
			CTexture* m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			Vec2 vPos = GetRenderPos();
			Vec2 vScale = GetScale();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(dc
				, (vPos.x - (m_Bridge->GetWidth()) / 2.f) + x_offset
				, (vPos.y - (m_Bridge->GetHeight()) / 2.f) + y_offset
				, m_Bridge->GetWidth()
				, m_Bridge->GetHeight()
				, m_Bridge->GetDC()
				, 0, 0
				, m_Bridge->GetWidth()
				, m_Bridge->GetHeight()
				, blend);
		}
		
	}

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);

}

void CJudmentPiston::CreateFireFlipbook()
{

	//CreatePngFlipbook(L"PISTON", L"sinPiston", 6);
	//CreatePngFlipbook(L"NULL_PISTON", L"sinPistonNull", 6);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(PISTON, CAssetMgr::GetInst()->LoadFlipbook(L"PISTON", L"Flipbook\\PISTON.flip"));
	m_FlipbookPlayer->AddFlipbook(NULL_PISTON, CAssetMgr::GetInst()->LoadFlipbook(L"NULL_PISTON", L"Flipbook\\NULL_PISTON.flip"));

}

void CJudmentPiston::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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