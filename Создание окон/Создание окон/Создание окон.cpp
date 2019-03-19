// �������� ����.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "�������� ����.h"
#include "cmath"

#define MAX_LOADSTRING 100

 // ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);

BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


LRESULT CALLBACK	WndGraph(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // ���� ��������� ���������:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


	WNDCLASSEX wcgraph = { 0 };
	wcgraph.cbSize = sizeof(WNDCLASSEX);
	wcgraph.style = CS_HREDRAW | CS_VREDRAW;
	wcgraph.lpfnWndProc = WndGraph;
	wcgraph.hInstance = hInst;
	wcgraph.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcgraph.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcgraph.lpszClassName = _T("WinClassGraphName");
	wcgraph.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcgraph);

    return RegisterClassExW(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//
//

LRESULT CALLBACK WndGraph(HWND, UINT, WPARAM, LPARAM);



HWND Sk;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	static double x1, y1, x2, y2, x3, y3, x4, y4, A, B;
		//C, D;
	



	switch (message)
	{

	case WM_SIZE:break;
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:

		RECT rect;
		GetWindowRect(hWnd, &rect);

		x1 = rect.top;		x2 = rect.top;
		y1 = rect.left;		y3 = rect.left;

		x3 = rect.bottom; 	x4 = rect.bottom;
		y2 = rect.right;	y4 = rect.right;

		//1. ������� �(TOP)
		A = sqrt(pow((x2-x1), 2)+pow((y2-y1), 2));

		//2. ������� �(LEFT)
		B= sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2));

		////3. ������� A(BOTTOM)
		//C= sqrt(pow((x4 - x3), 2) + pow((y4 - y3), 2));

		////4. ������� B(RIGHT)
		//D = sqrt(pow((x4 - x2), 2) + pow((y4 - y2), 2));


		if (IsWindow(Sk)) break;
		Sk = CreateWindow(_T("WinClassGraphName"), _T("����������� ����"), WS_SYSMENU | WS_POPUP | WS_VISIBLE | WS_THICKFRAME | WS_CAPTION,
				x1, y1, A/2, B/2, hWnd, 0, hInst, NULL);
		break;
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		if (IsWindow(Sk)) DestroyWindow(Sk);	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT: DestroyWindow(hWnd);	break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;

}


LRESULT CALLBACK WndGraph(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static HPEN hline;
	static int sx, sy;
	static HBRUSH hrect;
	RECT rt;
	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//DeleteObject(hline);
		//DeleteObject(hrect);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// ���������� ��������� ��� ���� "� ���������".
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
