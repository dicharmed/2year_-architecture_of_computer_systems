// листинг 3.6 текстовый редактор.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "листинг 3.6 текстовый редактор.h"
#include <commdlg.h>
#include <fstream>
#include <vector>
#include <string>
#include <commctrl.h>


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
const DWORD MaxLength = 0x7fff;
static TCHAR name[256] = _T("");;
static OPENFILENAME file;
std::ifstream in;
std::ofstream out;



TBBUTTON tbb[] =
{ 
	{ STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0 },
	{ STD_FILEOPEN, ID_FILE_OPEN,TBSTATE_ENABLED,TBSTYLE_BUTTON, 0, 0, 0, 0 },
	{ STD_FILESAVE, ID_FILE_SAVE,TBSTATE_ENABLED,TBSTYLE_BUTTON, 0, 0, 0, 0 }
};
//////////////////////////////////////////////////////////////////////
VOID StatusOut(HWND hStatus, int count, TCHAR *str)
{
	TCHAR text[256];
	_stprintf_s(text, _T("Строк: %d"), count);
	SendMessage(hStatus, SB_SETTEXT, (WPARAM)0, (LPARAM)text);
	SendMessage(hStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)str);
}
// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY36, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY36));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//



//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static OPENFILENAME file;
	static int n, sx, sy;
	static HWND hEdit, hWndToolBar, hWndStatusBar;
	RECT rt;
	int m, k, aWidths[2];
	static TCHAR name[256];
	char szText[0x7fff];
	std::ifstream in;
	std::ofstream out;


	switch (message)
	{
	case WM_CREATE:
		hWndToolBar = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | CCS_TOP,
			2, 0, HINST_COMMCTRL, IDB_STD_SMALL_COLOR, tbb, 3, 0, 0, 0, 0,
			sizeof(TBBUTTON));
		hEdit = CreateWindow(WC_EDIT, NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL |
			WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			0, 0, 0, 0, hWnd, (HMENU)1, hInst, NULL);
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("Text\0 *.txt\0Все файлы\0 *.*");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("txt");
		hWndStatusBar = CreateWindow(STATUSCLASSNAME, NULL, WS_CHILD |
			WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		aWidths[0] = 100;
		aWidths[1] = sx;
		GetWindowRect(hWndToolBar, &rt);
		m = rt.bottom - rt.top;
		SendMessage(hWndToolBar, TB_AUTOSIZE, 0, 0);
		GetWindowRect(hWndStatusBar, &rt);
		k = rt.bottom - rt.top;
		MoveWindow(hWndStatusBar, 0, sy - k, sx, sy, TRUE);
		SendMessage(hWndStatusBar, SB_SETPARTS, (WPARAM)2, (LPARAM)aWidths);
		StatusOut(hWndStatusBar, n, name);
		MoveWindow(hEdit, 0, m, sx, sy - m - k, TRUE);
		UpdateWindow(hEdit);
		SetFocus(hEdit);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			szText[0] = '\0';
			SetWindowTextA(hEdit, szText);
			StatusOut(hWndStatusBar, 0, _T(""));
			break;
		case ID_FILE_OPEN:
			file.lpstrTitle = _T("Открыть файл для чтения");
			file.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&file)) return 1;
			in.open(name, std::ios::binary);
			in.read(szText, 0x7fff);
			if ((m = in.gcount()) == 0x7fff)
			{
				MessageBox(hWnd, _T("Слишком большой файл"),
					_T("Edit"), MB_OK | MB_ICONSTOP);
				in.close();
				return 0;
			}
			szText[m] = '\0';
			in.close();
			SetWindowTextA(hEdit, szText);
			n = SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
			StatusOut(hWndStatusBar, n, name);
			break;
		case ID_FILE_SAVE:
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE | OFN_HIDEREADONLY;
			if (!GetSaveFileName(&file)) return 1;
			out.open(name, std::ios::binary);
			m = GetWindowTextA(hEdit, szText, 0x7fff);
			out.write(szText, m);
			out.close();
			n = SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
			StatusOut(hWndStatusBar, n, name);
			break;
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}
	

// Обработчик сообщений для окна "О программе".
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
