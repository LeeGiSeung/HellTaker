#include "pch.h"
#include "CJudmentCastle.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CLevelMgr.h"

void CJudmentCastle::Begin()
{
}

void CJudmentCastle::Tick()
{
}

void CJudmentCastle::Render()
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

    swprintf_s(filePath, 100, L"Texture\\front.png");
    swprintf_s(textureName, 100, L"front");
    CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , 460.f
        , 300.f
        , front->GetWidth() + 1080.f
        , front->GetHeight()
        , front->GetDC()
        , 0, 0
        , front->GetWidth()
        , front->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinShield.png");
    swprintf_s(textureName, 100, L"sinShield");
    CTexture* m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , (vPos.x - (m_Bridge->GetWidth())) + 50.f
        , 0.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinShieldRIGHT.png");
    swprintf_s(textureName, 100, L"sinShieldRIGHT");

    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , vPos.x - 70.f
        , 0.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinCore.png");
    swprintf_s(textureName, 100, L"sinCore");

    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , 230.f
        , 320.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinCoreRIGHT.png");
    swprintf_s(textureName, 100, L"sinCoreRIGHT");

    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , 1430.f
        , 320.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinPanel.png");
    swprintf_s(textureName, 100, L"sinPanel");
    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , (vPos.x - (m_Bridge->GetWidth())) - 62.5
        , 1920/2.f - 43.f + 20.f + 50.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinPanelRIGHT.png");
    swprintf_s(textureName, 100, L"sinPanelRIGHT");

    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , vPos.x + 42.5
        , 1920 / 2.f - 43.f + 20.f + 50.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
    const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
    CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

    if (cp->TalkCutSceneIndex == 1) {
        swprintf_s(filePath, 100, L"Texture\\1.png");
        swprintf_s(textureName, 100, L"1");
    }
    if (cp->TalkCutSceneIndex == 2) {
        swprintf_s(filePath, 100, L"Texture\\2.png");
        swprintf_s(textureName, 100, L"2");
    }
    if (cp->TalkCutSceneIndex == 3) {
        swprintf_s(filePath, 100, L"Texture\\3.png");
        swprintf_s(textureName, 100, L"3");
    }
    if (cp->TalkCutSceneIndex == 4) {
        swprintf_s(filePath, 100, L"Texture\\4.png");
        swprintf_s(textureName, 100, L"4");
    }


    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , 1920 / 2.f - 150.f + 10.f + 10.f - 8.f
        , 955.f + 50.f - 10.f
        , m_Bridge->GetWidth() * 0.5f
        , m_Bridge->GetHeight() * 0.5f
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);

    swprintf_s(filePath, 100, L"Texture\\sinEye.png");
    swprintf_s(textureName, 100, L"sinEye");

    m_Bridge = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

    AlphaBlend(dc
        , vPos.x - 190.f + 10.f + 10.f
        , 1920 / 2.f - 63.f + 40.f + 50.f - 10.f
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , m_Bridge->GetDC()
        , 0, 0
        , m_Bridge->GetWidth()
        , m_Bridge->GetHeight()
        , blend);
    HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
    ReleaseDC(hwnd, dc);
}

CJudmentCastle::CJudmentCastle()
{
}

CJudmentCastle::~CJudmentCastle()
{
}
