#include "pch.h"
#include "CBlackChain.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"

CBlackChain::CBlackChain()
{
}

CBlackChain::~CBlackChain()
{
}

void CBlackChain::Begin()
{
}

void CBlackChain::Tick()
{
}

void CBlackChain::Render()
{
    wchar_t filePath[100] = {};
    wchar_t textureName[100] = {};

    HDC dc = CEngine::GetInst()->GetSecondDC();
    Vec2 vPos = GetRenderPos();

    BLENDFUNCTION blend = {};

    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    swprintf_s(filePath, 100, L"Texture\\chainlink2.png");
    swprintf_s(textureName, 100, L"chainlink2");
    CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , (vPos.x - (front->GetWidth()) / 2.f)
        , vPos.y
        , front->GetWidth()
        , front->GetHeight()
        , front->GetDC()
        , 0, 0
        , front->GetWidth()
        , front->GetHeight()
        , blend);
    HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
    ReleaseDC(hwnd, dc);
}


