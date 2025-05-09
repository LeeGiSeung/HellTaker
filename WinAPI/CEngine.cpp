#include "pch.h"
#include "CEngine.h"

#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"
#include "CCollisionMgr.h"
#include "CSelectGDI.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"

CEngine::CEngine()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_Resolution{}
    , m_hDC(nullptr)
    , m_BackBuffer(nullptr)
    , m_Pen{}
    , m_Brush{}
{   
}

CEngine::~CEngine()
{
    // DC 해제
    ReleaseDC(m_hWnd, m_hDC);

    // Pen 과 Brush 해제
    for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
    {
        DeleteObject(m_Pen[i]);
    }

    for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
    {
        if (BRUSH_TYPE::HOLLOW == (BRUSH_TYPE)i)
            continue;

        DeleteObject(m_Brush[i]);
    }
}


int CEngine::Init(HINSTANCE _hInst, POINT _Resolution)
{
    m_hInst = _hInst;
    m_Resolution = _Resolution;

    // HWND 윈도우 ID 타입
    // 커널 오브젝트 ( OS 차원에서 관리되는 객체 )
    m_hWnd = CreateWindowW(L"Key", L"MyGame", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX),
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)   
        return E_FAIL;
    
    ShowWindow(m_hWnd, true);
    UpdateWindow(m_hWnd);

    // 윈도우 크기를 해상도에 맞게 설정
    ChangeWindowSize(m_Resolution, true);
    
    // DC 생성   
    m_hDC = GetDC(m_hWnd);

    // GDIObject 생성
    CreateGDIObject();    
  
    // Manager 생성 및 초기화
    CPathMgr::Init();
    CSoundMgr::GetInst()->Init();    
    CTimeMgr::GetInst()->Init();
    CKeyMgr::GetInst()->Init();
    CAssetMgr::GetInst()->Init();
    CLevelMgr::GetInst()->Init();
    CCamera::GetInst()->Init();
    

    // 더블버퍼링을 위한 추가버퍼 생성
    CreateSecondBuffer();


    return S_OK;
}

void CEngine::CreateGDIObject()
{
    // Pen
    m_Pen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    m_Pen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    m_Pen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

    // Brush
    m_Brush[(UINT)BRUSH_TYPE::RED]      = CreateSolidBrush(RGB(255, 0, 0));
    m_Brush[(UINT)BRUSH_TYPE::GREEN]    = CreateSolidBrush(RGB(0, 255, 0));
    m_Brush[(UINT)BRUSH_TYPE::BLUE]     = CreateSolidBrush(RGB(0, 0, 255));
    m_Brush[(UINT)BRUSH_TYPE::GRAY]     = CreateSolidBrush(RGB(2, 2, 27));
    //2 2 27
    m_Brush[(UINT)BRUSH_TYPE::HOLLOW]   = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}



void CEngine::Progress()
{
    // Manager Tick
    CTimeMgr::GetInst()->Tick(); // DT 계산
    CKeyMgr::GetInst()->Tick();  // 각 키의 상태
    CDbgRender::GetInst()->Tick();
    CCamera::GetInst()->Tick();

    // 레벨 실행
    CLevelMgr::GetInst()->Progress();

    // 충돌 검사 실행
    CCollisionMgr::GetInst()->Tick();

    // UI 매니저 체크
    CUIMgr::GetInst()->Tick();


    // 렌더링
    // 화면 클리어
    {
        SELECT_BRUSH(BRUSH_TYPE::GRAY);
        Rectangle(m_BackBuffer->GetDC(), -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
    }

    // 레벨 렌더링
    CLevelMgr::GetInst()->Render();

    // Camera 렌더링
    CCamera::GetInst()->Render();

    // 디버그 정보 렌더링
    CDbgRender::GetInst()->Render();

    // SecondBitmap 있는 장면을 MainWindowBitmap 으로 복사해온다.
    BitBlt(m_hDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y
        , m_BackBuffer->GetDC(), 0, 0, SRCCOPY);

    // TaskMgr 동작
    CTaskMgr::GetInst()->Tick();
}


void CEngine::ChangeWindowSize(Vec2 _vResolution, bool fullscreen)
{
    m_Resolution = _vResolution;

    if (fullscreen)
    {
        // 전체 화면 모드
        LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
        style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        SetWindowLong(m_hWnd, GWL_STYLE, style);

        // 모니터 크기 가져오기
        HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi = { sizeof(mi) };
        if (GetMonitorInfo(hMonitor, &mi))
        {
            SetWindowPos(m_hWnd, HWND_TOP,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }
    else
    {
        // 창 모드
        LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
        style |= (WS_OVERLAPPEDWINDOW);
        SetWindowLong(m_hWnd, GWL_STYLE, style);

        // 해상도에 맞는 크기로 조정
        RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
        HMENU hMenu = GetMenu(m_hWnd);
        AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

        SetWindowPos(m_hWnd, nullptr,
            0, 0,
            rt.right - rt.left,
            rt.bottom - rt.top,
            SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }

    //m_Resolution = _vResolution;   

    //RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };

    //// 메인윈도우가 Menu 가 있는지 확인
    //HMENU hMenu = GetMenu(m_hWnd);

    //AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

    //SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateSecondBuffer()
{
    m_BackBuffer = CAssetMgr::GetInst()->CreateTexture(L"BackBuffer", (int)m_Resolution.x, (int)m_Resolution.y);
}