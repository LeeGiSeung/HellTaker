#include "pch.h"

#include "CGear.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CFlipbookPlayer.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CFlipbook.h"

enum GEAR_STATE
{
	GEAR_RUN,
	GEAR_STOP
};

enum GEAR_DIR {
	LEFT_GEAR,
	RIGHT_GEAR
};

CGear::CGear()
	:m_FlipbookPlayer(nullptr)
{
	CreateFireFlipbook();
}

CGear::~CGear()
{
}


void CGear::Begin()
{
	if (gear == 0) {
		m_FlipbookPlayer->Play(LEFT_GEAR, 40.f, true);
	}
	else {
		m_FlipbookPlayer->Play(RIGHT_GEAR, 40.f, true);
	}
	
}

void CGear::Tick()
{
}

void CGear::Render()
{

	HDC dc = CEngine::GetInst()->GetSecondDC();
	if (GearTurn) {
		m_FlipbookPlayer->Fire_Render(x_offset, y_offset, 1.f);
	}
	else {
		if (gear == 0) {
			
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			Vec2 vPos = GetRenderPos();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			swprintf_s(filePath, 100, L"Texture\\sinGears_0.png");
			swprintf_s(textureName, 100, L"sinGears_0");
			CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				,vPos.x - (front->GetWidth()) / 2.f + x_offset
				,vPos.y - (front->GetHeight()) / 2.f + y_offset
				, front->GetWidth()
				, front->GetHeight()
				, front->GetDC()
				, 0, 0
				, front->GetWidth()
				, front->GetHeight()
				, blend);
		}
		else {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			Vec2 vPos = GetRenderPos();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			swprintf_s(filePath, 100, L"Texture\\sinGearsRIGHT_0.png");
			swprintf_s(textureName, 100, L"sinGearsRIGHT_0");
			CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, vPos.x - (front->GetWidth()) / 2.f + x_offset
				, vPos.y - (front->GetHeight()) / 2.f + y_offset
				, front->GetWidth()
				, front->GetHeight()
				, front->GetDC()
				, 0, 0
				, front->GetWidth()
				, front->GetHeight()
				, blend);
		}
		
	}

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);

}

void CGear::CreateFireFlipbook()
{
	//CreatePngFlipbook(L"LEFT_GEAR", L"sinGears", 15);
	//CreatePngFlipbook(L"RIGHT_GEAR", L"sinGearsRIGHT", 15);

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(LEFT_GEAR, CAssetMgr::GetInst()->LoadFlipbook(L"LEFT_GEAR", L"Flipbook\\LEFT_GEAR.flip"));
	m_FlipbookPlayer->AddFlipbook(RIGHT_GEAR, CAssetMgr::GetInst()->LoadFlipbook(L"RIGHT_GEAR", L"Flipbook\\RIGHT_GEAR.flip"));

}

void CGear::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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