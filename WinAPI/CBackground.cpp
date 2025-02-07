#include "pch.h"
#include "CBackground.h"

#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CBackground::CBackground()
	:m_Tex(nullptr)
{
}

CBackground::~CBackground()
{
}

void CBackground::SetBackgroundMap(const wstring& _Pngname)
{
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};
	// 각 프레임에 대한 경로 생성
	swprintf_s(filePath, 100, L"Texture\\%s.png", _Pngname.c_str());
	swprintf_s(textureName, 100, L"%s", _Pngname.c_str());

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	m_Tex = pAtlas;
}

void CBackground::Begin()
{
}

void CBackground::Tick()
{
}

void CBackground::Render()
{

	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	if (cp->CurLevel == BOSS_0) {

		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		swprintf_s(filePath, 100, L"Texture\\sinPit.png");
		swprintf_s(textureName, 100, L"sinPit");

		CTexture* sinPit = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		HDC dc = CEngine::GetInst()->GetSecondDC();

		Vec2 vPos = GetRenderPos();
		Vec2 vScale = GetScale();

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(dc
			, 0
			, 0
			, sinPit->GetWidth()
			, sinPit->GetHeight()
			, sinPit->GetDC()
			, 0, 0
			, sinPit->GetWidth()
			, sinPit->GetHeight()
			, blend);

		AlphaBlend(dc
			, 0
			, 656
			, sinPit->GetWidth()
			, sinPit->GetHeight()
			, sinPit->GetDC()
			, 0, 0
			, sinPit->GetWidth()
			, sinPit->GetHeight()
			, blend);

		swprintf_s(filePath, 100, L"Texture\\sinPitRIGHT.png");
		swprintf_s(textureName, 100, L"sinPitRIGHT");

		CTexture* sinPitRIGHT = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, 1426
			, 0
			, sinPitRIGHT->GetWidth()
			, sinPitRIGHT->GetHeight()
			, sinPitRIGHT->GetDC()
			, 0, 0
			, sinPitRIGHT->GetWidth()
			, sinPitRIGHT->GetHeight()
			, blend);

		AlphaBlend(dc
			, 1426
			, 656
			, sinPitRIGHT->GetWidth()
			, sinPitRIGHT->GetHeight()
			, sinPitRIGHT->GetDC()
			, 0, 0
			, sinPitRIGHT->GetWidth()
			, sinPitRIGHT->GetHeight()
			, blend);

		swprintf_s(filePath, 100, L"Texture\\sinMist.png");
		swprintf_s(textureName, 100, L"sinMist");

		CTexture* OrangeMist = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, 0
			, 0
			, OrangeMist->GetWidth() + 800.f
			, OrangeMist->GetHeight()
			, OrangeMist->GetDC()
			, 0, 0
			, OrangeMist->GetWidth()
			, OrangeMist->GetHeight()
			, blend);

		AlphaBlend(dc
			, 1200
			, 0
			, OrangeMist->GetWidth() + 800.f
			, OrangeMist->GetHeight()
			, OrangeMist->GetDC()
			, 0, 0
			, OrangeMist->GetWidth()
			, OrangeMist->GetHeight()
			, blend);

		HBRUSH hBrush = CreateSolidBrush(RGB(30, 4, 30));

		HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);

		Rectangle(dc
			, 500, 0
			, (int)(1500)
			, (int)(700));

		SelectObject(dc, hPrevBrush);
		SelectObject(dc, hBrush); // 이전 브러시 복원
		DeleteObject(hBrush);
		DeleteObject(hPrevBrush);

		swprintf_s(filePath, 100, L"Texture\\sinMaw_resized.png");
		swprintf_s(textureName, 100, L"sinMaw_resized");
		CTexture* m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, 421.f
			, 305.5f
			, m_Bridge->GetWidth() * 1.20f
			, m_Bridge->GetHeight()
			, m_Bridge->GetDC()
			, 0, 0
			, m_Bridge->GetWidth()
			, m_Bridge->GetHeight()
			, blend);

		AlphaBlend(dc
			, 1360.f
			, 305.5f
			, m_Bridge->GetWidth() * 1.20f
			, m_Bridge->GetHeight()
			, m_Bridge->GetDC()
			, 0, 0
			, m_Bridge->GetWidth()
			, m_Bridge->GetHeight()
			, blend);
		hBrush = CreateSolidBrush(RGB(112, 12, 41));
		hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);
		Rectangle(dc
			, 520, 400
			, (int)(1340)
			, (int)(1000));
	}
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(dc
		, vPos.x
		, vPos.y
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
