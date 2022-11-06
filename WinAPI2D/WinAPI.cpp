// WinAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "WinAPI.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
HWND hWnd;										// �������� �ڵ�
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// ������ ���α׷��� ���� �Լ�
/// 1. ������â�� ���� �� ȭ�鿡 ���
/// 2. �޼��� ������ ���α׷� ������� ��� �ݺ�
/// </summary>
/// <param name="hInstance"> ����� ���μ����� ���� �ּ�. �ν��Ͻ� �ڵ� </param>
/// <param name="hPrevInstance"> ������ ����� �ν��Ͻ� �ڵ� </param>
/// <param name="lpCmdLine"> ������� �Էµ� ���α׷��� �μ� </param>
/// <param name="nCmdShow"> ���α׷��� ���۵� ���� </param>
/// <returns> ���ø����̼��� �ʱ�ȭ �Ұ��� �� False, �޼��� �������� ���Ḧ �Է¹޾��� �� �޼����� wParam </returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // �ѱ� ���� ����
    setlocale(LC_ALL, "Korean");
    // �޸� ���� üũ
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(219);

    // ������� ���� �Ű����� ����
    // ���ʿ��� �Ű����������� ������ �����츦 �����ϱ� ���� �״�� ��
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ���ҽ� ���� String table ����
    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // ���ҽ� ���� ����Ű ����
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    // �⺻ �޽��� �����Դϴ�: GetMessage
    // �޼��� ť���� �޼����� Ȯ�ε� ������ ���
    // �޼��� ť�� msg.mssage == WM_QUIT �� ��� false�� ��ȯ
    /*
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))	// ����Ű ó��
        {
            TranslateMessage(&msg);	// Ű���� �Է¸޼��� ó���� ���
            DispatchMessage(&msg);	// WndProc���� ���޵� �޼����� ���� �����쿡 ����
        }
    }
    */

    // ���� �޼��� �����Դϴ�: PeekMessage
    // �޼��� ť���� �޼����� ���ٸ� ������� �ʰ� false ��ȯ, �޼����� �ִٸ� true ��ȯ
    // �޼����� ���� ��κ��� ��Ȳ���� ���� ��Ȳ�� ó��
    // �޼��� ť�� msg.message == WM_QUIT �� ��� ���� �޼��� ������ break�Ͽ� ���α׷� ����
    CORE->Init();

    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))    // �޽��� ������ ����ó��, �޽��� ������ �޽���ó��
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // ����Ű�� ���� ó��
            {
                TranslateMessage(&msg);     // Ű���� �Է¸޼��� ó���� ���
                DispatchMessage(&msg);      // WndProc���� ���޵� �޼����� ���� �����쿡 ����
            }
        }
        else
        {
            // ���� ó��
            CORE->Update();
            CORE->Render();
        }

    }
    CORE->Release();

    return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // ������ â�� ������ �����ϱ� ���� ����ü
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);	// ����ü�� ũ�� ����

    wcex.style = CS_HREDRAW | CS_VREDRAW;	// ������ Ŭ������ ��Ÿ�� ����
    wcex.lpfnWndProc = WndProc;	// �޼����� ó���ϴ� �Լ��� ����(������ ���ν���)
    wcex.cbClsExtra = 0;	// ������ Ŭ�������� ����ϰ��� �ϴ� ������ �޸𸮾��� ����Ʈ ������ ����
    wcex.cbWndExtra = 0;	// cbClsExtra�� �����ϳ� ���� �����쿡�� ����ϰ��� �ϴ� ������ �޸𸮾��� ����
    wcex.hInstance = hInstance;	// ������ Ŭ������ ����� �ν��Ͻ��� �ڵ�
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));	// ���α׷� ������
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));	// ���α׷� ���������� ������
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);	// Ŀ�� ����
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);	// ������ �۾������� ĥ�� ��� �귯��
    wcex.lpszMenuName = nullptr;	// �����쿡�� ����� �޴� ����. nullptr�� ����
    wcex.lpszClassName = szWindowClass;	// ������ Ŭ������ �̸�

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    hWnd = CreateWindowW(
        szWindowClass,		// ������ Ŭ���� �̸�
        szTitle,				// ������ Ÿ��Ʋ �̸�
        WINSTYLE,			// ������ ��Ÿ��
        WINSTARTX,			// ������ ȭ�� X
        WINSTARTY,			// ������ ȭ�� Y
        WINSIZEX,			// ������ ���� ũ��
        WINSIZEY,			// ������ ���� ũ��
        nullptr,				// �θ� ������
        nullptr,				// �޴� �ڵ�
        hInstance,			// �ν��Ͻ� ����
        nullptr				// �߰� �Ű�����
    );

    if (!hWnd)
    {
        return FALSE;
    }

    // ���� ������ ũ�⸦ ���ϱ� ���� AdjustWindowRect ���
    RECT rc = { 0, 0, WINSIZEX, WINSIZEY };

    // ���� â�� ũ�⿡ �°� ���´�.
    AdjustWindowRect(&rc, WINSTYLE, false);
    // �� RECT������ ������ ����� ����
    SetWindowPos(hWnd, NULL, WINSTARTX, WINSTARTY, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

/// <summary>
/// �޼����� �ü���� ����
/// ������ �ü���� ȣ����
/// </summary>
/// <param name="hWnd"> �޼����� ��� �����츦 ������� ���޵Ǿ����� ���� </param>
/// <param name="message"> �޼��� ���� ��ȣ </param>
/// <param name="wParam"> �޼����� �Ű����� 1 </param>
/// <param name="lParam"> �޼����� �Ű����� 2 </param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:	// ������� �޼���
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    // �������� ȭ�� ��¿� �޼���
    // �������� �۾������� �ٽ� �׷����� �Ҷ� �����
    // -> ��ȿȭ ������ �߻� ���� ��
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;

    // �����찡 ����� �� �����
    // -> �޼��� ť�� WM_QUIT �Է�
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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