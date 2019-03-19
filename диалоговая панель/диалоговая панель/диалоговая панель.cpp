// диалоговая панель.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "диалоговая панель.h"

#include <commctrl.h>
#include "resource.h"
#include <windows.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LOADSTRING 100


BOOL CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MY_DIALOG), NULL, (DLGPROC)DlgProc);
	if (ret == 0)
	{
		//Если была нажата кнопка Отмена или крестик
		//MessageBox(NULL, (LPCTSTR)"Отмена", (LPCTSTR)"Inform",MB_OK | MB_ICONINFORMATION);
	}
	else if (ret == 1)
	{
		//Если была нажата кнопка Ок
		//MessageBox(NULL, (LPCTSTR)"Ок", (LPCTSTR)"Inform",MB_OK | MB_ICONINFORMATION);
	}

	return ret;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return FALSE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			//case IDC_BUTTON1:
			//{
			//	char buf[250];
			//	//получаем данные из поля IDC_EDIT1
			//	GetDlgItemText(hwnd, IDC_EDIT1, buf, sizeof(buf));
			//	//отправляем данные в IDC_EDIT2
			//	SetDlgItemText(hwnd, IDC_EDIT2, buf);
			//	//очищаем само поле
			//	SetDlgItemText(hwnd, IDC_EDIT1, "");
			//	//дальше прорисовывается окно
			//	return FALSE;
			//}
			//case IDC_BUTTON2:
			//{
			//	SetDlgItemText(hwnd, IDC_EDIT1, "Hellow world!!!");
			//	SetDlgItemText(hwnd, IDC_EDIT2, "Hellow world!!!");
			//	return FALSE;
			//}
			//case IDC_BUTTON3:
			//{
			//	SetDlgItemText(hwnd, IDC_EDIT1, "");
			//	SetDlgItemText(hwnd, IDC_EDIT2, "");
			//	return FALSE;
			//}
		case IDOK:
		{
			TCHAR buf[250];
			TCHAR buf1[250];
			//получаем данные из поля IDC_EDIT1
			GetDlgItemText(hwnd, IDC_EDIT1, buf, sizeof(buf));
			//получаем данные из поля IDC_EDIT1
			GetDlgItemText(hwnd, IDC_EDIT2, buf1, sizeof(buf1));

			//TCHAR **a = new TCHAR*[2];// Создаем массив указателей
			//for (int i = 0; i < 2; i++)
			//{
			//	a[i] = new TCHAR[2]; // Создаем элементы
			//}
			//// А дальше работа как с обычным массивом. 
			//for (int i = 0; i < 2; i++)
			//{
			//	for (int j = 0; j < 2; j++)
			//	{
			//		a[i][j] = rand() % 10; // Каждый элемент случайному числу от 0 до 9
			//		//cout << a[i][j] << " "; // Вывести элементы на консольку

			//		SetDlgItemText(hwnd, IDC_EDIT3, a[i]);
			//		SetDlgItemText(hwnd, IDC_EDIT3, a[j]);
			//	
			//	}
			//	
			//}// Удаление массива
			//	for (int i = 0; i < 2; i++)
			//	{
			//		delete[]a[i]; // Удаляем каждый элемент
			//	}
			//	delete[] a; // А потом массив
			//	return 0;
			//	//отправляем данные в IDC_EDIT2

	


			int mas[3][2] = {{1,2,}, {9,7,},  {3,4,} };
			HDC hdc;
			hdc = GetDC(hwnd);
			char text[100];
			//char text[100];	
			char rttt[100]=" ";
			int sum=0;

			for (int i = 0; i < 3; i++) //переключение по строкам
			{
				for (int j = 0; j < 2; j++)// переключение по столбцам
				{
					
					_itoa_s(mas[i][j],text, 10);
					SetDlgItemTextA(hwnd, IDC_EDIT3, (LPCSTR)text);
					
					//wcscpy_s(rttt, (LPWSTR)text);

				//	_tcscpy_s(rttt, (LPWSTR)text);
					
					//SetDlgItemText(hwnd, IDC_EDIT3, (LPWSTR)mas[j]);

					

					
				}
			}
			ReleaseDC(hwnd, hdc);

		}
		case IDC_EDIT1:
		{
			return FALSE;
		}
		case IDC_EDIT2:
		{
			return FALSE;
		}
		}
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, 0);
		return FALSE;
	}
	}
	return FALSE;//нужно что бы вызвать функцию для прорисовки окда
}