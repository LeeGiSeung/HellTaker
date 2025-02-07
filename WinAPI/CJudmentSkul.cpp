#include "pch.h"
#include "CJudmentSkul.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"

void CJudmentSkul::Begin()
{
}

void CJudmentSkul::Tick()
{
}

void CJudmentSkul::Render()
{

    HDC dc = CEngine::GetInst()->GetSecondDC();

    if (dir == 0 && Under == false) {
        wchar_t filePath[100] = {};
        wchar_t textureName[100] = {};

        Vec2 vPos = GetRenderPos();

        BLENDFUNCTION blend = {};

        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;
        blend.SourceConstantAlpha = 255;
        blend.AlphaFormat = AC_SRC_ALPHA;

        swprintf_s(filePath, 100, L"Texture\\sinArm.png");
        swprintf_s(textureName, 100, L"sinArm");
        CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

        AlphaBlend(dc
            , (vPos.x - (front->GetWidth()) / 2.f) + 115.f
            , (vPos.y - (front->GetHeight()) / 2.f) + 50.f
            , front->GetWidth()
            , front->GetHeight()
            , front->GetDC()
            , 0, 0
            , front->GetWidth()
            , front->GetHeight()
            , blend);
    }
    else if(dir == 1 && Under == false) {
        wchar_t filePath[100] = {};
        wchar_t textureName[100] = {};

        Vec2 vPos = GetRenderPos();

        BLENDFUNCTION blend = {};

        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;
        blend.SourceConstantAlpha = 255;
        blend.AlphaFormat = AC_SRC_ALPHA;

        swprintf_s(filePath, 100, L"Texture\\sinArmRIGHT.png");
        swprintf_s(textureName, 100, L"sinArmRIGHT");
        CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

        AlphaBlend(dc
            , (vPos.x - (front->GetWidth()) / 2.f) - 150.f
            , (vPos.y - (front->GetHeight()) / 2.f) + 50.f
            , front->GetWidth()
            , front->GetHeight()
            , front->GetDC()
            , 0, 0
            , front->GetWidth()
            , front->GetHeight()
            , blend);
    }

    if (Under) {
        wchar_t filePath[100] = {};
        wchar_t textureName[100] = {};

        Vec2 vPos = GetRenderPos();

        BLENDFUNCTION blend = {};

        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;
        blend.SourceConstantAlpha = 255;
        blend.AlphaFormat = AC_SRC_ALPHA;

        swprintf_s(filePath, 100, L"Texture\\sinSkull0001.png");
        swprintf_s(textureName, 100, L"sinSkull0001");
        CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

        AlphaBlend(dc
            , (vPos.x - (front->GetWidth()) / 2.f)
            , (vPos.y - (front->GetHeight()) / 2.f)
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

        swprintf_s(filePath, 100, L"Texture\\sinSkull0002.png");
        swprintf_s(textureName, 100, L"sinSkull0002");
        CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

        AlphaBlend(dc
            , (vPos.x - (front->GetWidth()) / 2.f)
            , (vPos.y - (front->GetHeight()) / 2.f)
            , front->GetWidth()
            , front->GetHeight()
            , front->GetDC()
            , 0, 0
            , front->GetWidth()
            , front->GetHeight()
            , blend);
    }

    HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
    ReleaseDC(hwnd, dc);

}

CJudmentSkul::CJudmentSkul()
{
}

CJudmentSkul::~CJudmentSkul()
{
}
