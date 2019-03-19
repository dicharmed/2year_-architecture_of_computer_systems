// ������� 3.6 ��������� ��������.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "������� 3.6 ��������� ��������.h"
#include <commdlg.h>
#include <string>
#include <commctrl.h>


#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����








// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_MY36, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY36));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY36));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY36);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


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



//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndStatusBar;
	static POINT  ptCursor;
	static HDC    hDC;
	int pParts[2];
	TCHAR textT[256];

	PAINTSTRUCT ps;
	RECT r;
	HBRUSH hBrush;
	static int fl;
		switch (message)
		{
			case WM_CREATE:
			{	
				hWndStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE,(LPTSTR)" ",hWnd,	IDS_STATUSBAR);					
				pParts[0] = 200;
				pParts[1] = 200+100+100;
				SendMessage(hWndStatusBar, SB_SETPARTS, 2, (LPARAM)&pParts);
				break;
			}

			case WM_SIZE:
			{
				SendMessage(hWndStatusBar, WM_SIZE, 0, 0);break;
			}
			case WM_COMMAND:
			{
				switch (LOWORD(wParam))
				{
				case ID_P1:	SendMessage(hWndStatusBar, SB_SETTEXT, 1, (LPARAM)_T("�����1")); fl = 1; break;

				case ID_P2:	SendMessage(hWndStatusBar, SB_SETTEXT, 1, (LPARAM)_T("�����2")); fl = 2; break;

				case IDM_EXIT: DestroyWindow(hWnd); break;
					//default: return DefWindowProc(hWnd, message, wParam, lParam);
				}
				break;
			}
	
			case WM_MOUSEMOVE:
			{
				GetCursorPos(&ptCursor);
				hDC = GetDC(hWnd);
			
				//TextOut(hDC, 0, 0, szMsg, lstrlen(szMsg));	
		
				_stprintf_s(textT, _T("X: %d; Y: %d"), ptCursor.x, ptCursor.y);
				SendMessage(hWndStatusBar, SB_SETTEXT, (WPARAM)0, (LPARAM)textT);
				ReleaseDC(hWnd, hDC);
				break;
			}			
		case WM_DESTROY:
			PostQuitMessage(0);
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
