#include "pch.h"
#include "CFireBase.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"

CFireBase::CFireBase()
	: m_FlipbookPlayer(nullptr)
	, m_Tex(nullptr)
	, FLAMBASENum(0)
{
}

CFireBase::~CFireBase()
{
}


void CFireBase::Begin()
{
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};
	// 각 프레임에 대한 경로 생성
	if (FLAMBASENum == 0) {
		swprintf_s(filePath, 100, L"Texture\\FLAMEbase_0.png");
		swprintf_s(textureName, 100, L"FLAMEbase_0");
	}
	else if (FLAMBASENum == 1) {
		swprintf_s(filePath, 100, L"Texture\\FLAMEbase_1.png");
		swprintf_s(textureName, 100, L"FLAMEbase_1");
	}


	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	m_Tex = pAtlas;
}

void CFireBase::Tick()
{
}

void CFireBase::Render()
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

