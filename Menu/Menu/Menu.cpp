// Menu.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Menu.h"

#define MAX_LOADSTRING 100

#define CM_HIDDEN 2003

#define CM_VISIBLE 2004

#define CM_EXIT 2005

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
TCHAR szClass[] = TEXT("FloatMenu");
// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL RegClass(WNDPROC, LPCTSTR, UINT);

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
    LoadStringW(hInstance, IDC_MENU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MENU));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MENU));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MENU);
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
BOOL RegClass(WNDPROC Proc, LPCTSTR szName, UINT brBackground, HINSTANCE hInstance)
{

	WNDCLASS wc;
	wc.style = wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.lpfnWndProc = Proc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(brBackground + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szName;
	return (RegisterClass(&wc) != 0);
}
BOOL CreateMenuItem(HMENU hMenu, TCHAR *str, UINT uIns, UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType)

{

	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.fType = fType;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = str;
	mii.cch = sizeof(str);
	mii.wID = uCom;
	mii.hSubMenu = hSubMenu;

	return InsertMenuItem(hMenu, uIns, flag, &mii);

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
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
    case WM_COMMAND:
        {
			switch (LOWORD(wParam))
			{
				case CM_HIDDEN: ShowCursor(0); break;
				case CM_VISIBLE: ShowCursor(1); break;
				case CM_EXIT: DestroyWindow(hwnd); break;				
				
				case ID_HIDDEN: ShowCursor(0); break;
				case ID_VISIBLE: ShowCursor(1); break;
				case IDM_EXIT: DestroyWindow(hwnd); break;

			}				
        }break;
        
	case WM_RBUTTONDOWN:
	{

		//����� �������� ���������� ������� ����
		DWORD xyPos = GetMessagePos();
		WORD xPos = LOWORD(xyPos), yPos = HIWORD(xyPos);

		HMENU hFloatMenu = CreatePopupMenu();
		int i = 0;
		CreateMenuItem(hFloatMenu, TEXT("��������� ������"), i++, CM_HIDDEN, NULL, FALSE, MFT_STRING);
		CreateMenuItem(hFloatMenu, TEXT("������� ������"), i++, CM_VISIBLE, NULL, FALSE, MFT_STRING);
		CreateMenuItem(hFloatMenu, TEXT("�����"), i++, CM_EXIT, NULL, FALSE, MFT_STRING);
		//������� ���� � ������� ������� ����
		//TPM_LEFTBUTTON	���� ���� ������ ����������, ������������  ����� ������� ����� ���� ������ ����� ������� ����.
		//TPM_VCENTERALIGN	���� ���� ������ ����������, 
		//������� ����������� �� ������ ��������� ����������� ����, ������������ ����������, �������� ���������� y. 
		//TPM_CENTERALIGN	���� ���� ������ ����������, ������� ����������� �� ������ ����������� ����������� ����,
		//������������ ����������, ������������ ���������� x. 
		TrackPopupMenu(hFloatMenu, TPM_CENTERALIGN | TPM_LEFTBUTTON | TPM_VCENTERALIGN, xPos, yPos, 0, hwnd, NULL);
		DestroyMenu(hFloatMenu);
		return 0;

	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
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
