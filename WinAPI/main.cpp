#include "pch.h"

#include "WinAPI.h"
#include "CEngine.h"

HINSTANCE g_hInst = nullptr;
HWND      g_hDlg = nullptr;

// 전역 변수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// SAL : 주석 언어
int APIENTRY wWinMain(HINSTANCE hInstance   // 프로세스 주소(ID)
                    , HINSTANCE hPrevInstance // 안쓰이는 인자
                    , LPWSTR lpCmdLine
                    , int   nCmdShow)
{    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(18);

    g_hInst = hInstance; // 프로세스 시작 주소

    WNDCLASSEXW wcex = {};

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = &WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr;// MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = L"Key";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    // Engine 초기화
    if (FAILED(CEngine::GetInst()->Init(g_hInst, POINT{ 1920, 1080 })))
        return FALSE;


    // 단축키 테이블 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    // 메시지 변수
    MSG msg = {};
    
    while (true)
    {        
        // 메세지큐에 메세지가 있다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {          
            if (WM_QUIT == msg.message)
                break;

            // 메세지 처리
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // 메세지큐에 메세지가 없다.
        else
        {          
            // 게임 실행, 1 프레임
            CEngine::GetInst()->Progress();
        }              
    }

    return (int) msg.wParam;
}


bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            if (EditorMenu(g_hInst, hWnd, wmId))
            {
                break;
            }
            
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                // Modal
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, &About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE: 
    {
        int a = 0;
    }
        break;
    case WM_SIZE:

        break;           

    case WM_SIZING:

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void EnableFullscreen(HWND hwnd) {
    // 기존 스타일 저장
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

    // 스타일에서 제목 표시줄과 경계선을 제거
    style &= ~(WS_CAPTION | WS_THICKFRAME);
    exStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);

    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    // 화면 크기 얻기
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    if (GetMonitorInfo(hMonitor, &mi)) {
        SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
            mi.rcMonitor.right - mi.rcMonitor.left,
            mi.rcMonitor.bottom - mi.rcMonitor.top,
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
}
