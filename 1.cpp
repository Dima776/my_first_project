#include <windows.h>
#include "resource.h"
#include <string>
#include <tchar.h>
#include <vector>
using namespace std;

//хэндл немодального окна
HWND hDlgModeless,hEdit1,hstatic, hstatic_st,hstatic_lib,	hlist_lib,	hlist_st;

//используется для получения индекса в списке 
LRESULT ind=LB_ERR; //LB_ERR  в winuser.h определена как -1//как не  для LRESULT

//прототипы процедуры главного окна и модального диалогового окона
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModalSt(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModalLib(HWND, UINT, WPARAM, LPARAM);

wchar_t str[400];
//структура данных для хранения персональной информации
typedef struct
{
	wchar_t FullName[50];	
	wchar_t Date[50];
	//wchar_t Phone[50]; тут должно быть про наличие 
	wchar_t Writer[50];//тут был емайл
	//wchar_t Address[50];	
	//wchar_t money[50];	
}INFO;

//изначальное заполнение массива структур
//INFO info[SIZE]={
//	{TEXT("Скоробогатов Антон"), TEXT("7 февраля 1991"), TEXT("anton1991@mail.ru"), /*TEXT("ул.Новокузнецкая, д.25, кв.2"),TEXT("16587421")*/},
//	{TEXT("Михайленко Николай"), TEXT("17 января 1990"),  TEXT("nick1990@mail.ru"),/* TEXT("ул.Степная, д.11"),TEXT("16587421)"*/},
//	{TEXT("Филоненко Анастасия"), TEXT("4 марта 1991"),  TEXT("nastya@mail.ru")/*, TEXT("ул.Морская, д.14, кв.12"),TEXT("16587421")*/},
//	{TEXT("Духницкий Иван"), TEXT("8 июля 1991"), TEXT("ivan_duh@google.com")/*, TEXT("ул.Патриотическая, д.1, кв.15"),TEXT("16587421")*/},
//	{TEXT("Шматко Мария"), TEXT("17 апреля 1990"),  TEXT("maria_maria@yandex.ru")/* ,TEXT("ул.Портовая, д.17, кв.75"),TEXT("16587421")*/},
//	{TEXT("Переверзева Анна"), TEXT("21 сентября 1991"),  TEXT("anna91@pisem.net")/*, TEXT("ул.Вокзальная, д.12-а, кв.51"),TEXT("16587421")*/},
//	{TEXT("Синченко Ярослав"), TEXT("6 декабря 1990"),  TEXT("yaric@ukr.net") /*,TEXT("ул.Богдана Хмельницкого, д.3"),TEXT("16587421")*/},
//	{TEXT("Миллер Борис"), TEXT("10 августа 1991"), TEXT("miller_boris@yandex.ru")/*, TEXT("ул.Заводская, д.2, кв.10"),TEXT("16587421")*/},
//	{TEXT("Зинкевич Роман"), TEXT("16 марта 1989"),	 TEXT("roman@ukr.net")/*, TEXT("ул.Правды, д.18, кв.17"),TEXT("16587421")*/},
//	{TEXT("Светличный Павел"), TEXT("10 февраля 1991"),  TEXT("pasha@yandex.ru")/*, TEXT("ул.Молодёжная, д.54, кв.142"),TEXT("16587421")*/},
//	};
//
////на основе статического массива создаём вектор
//vector<INFO> v(info, info+SIZE);

////дальше все походу описывать в самих модульных окнах 
////функция заполнения статика 
//void fillStatic(int index)
//{
////	wcscpy_s(str, TEXT("Адрес:\n"));						
////	wcscat_s(str, v[index].Address);
//	wcscat_s(str, TEXT("\nДата рождения:\n"));
//	wcscat_s(str, v[index].Date);
////	wcscat_s(str, TEXT("\nТелефон:\n"));
////	wcscat_s(str, v[index].Phone);
//	wcscat_s(str, TEXT("\nЭлектронный адрес:\n"));
//	wcscat_s(str, v[index].Writer);
////	wcscat_s(str, TEXT("\nMoney:\n"));
//	//wcscat_s(str, v[index].money);
//	//SetWindowText(hwndStatic, str);	// тут описать два статика 
//	SetWindowText(hstatic_st,str);
//	
//}

//
////функция удаления элемента
//void delElement()
//{
//	//получаем индекс выделенного элемента списка
//	ind=SendMessage(hwndList, LB_GETCURSEL, 0, 0);	
//	//удаляем элемент из списка
//	SendMessage(hwndList, LB_DELETESTRING, ind, 0);
//	//удаляем элемент из вектора
//	v.erase(v.begin()+ind);
//	//очищаем статик
//	SetWindowText(hwndStatic, TEXT(""));	
//}
//
////функция добавления элемента
//void addElement()
//{
//	INFO add;	
//	//получаем информацию о добавляемом элементе из тестовых полей
//	GetWindowText(hwnd1, add.FullName, sizeof(add.FullName));
////	GetWindowText(hwnd2, add.Address, sizeof(add.Address));										
//	GetWindowText(hwnd3, add.BirthDate, sizeof(add.Date));							
//	//GetWindowText(hwnd4, add.Phone, sizeof(add.Phone));					
//	GetWindowText(hwnd5, add.Email, sizeof(add.Writer));
//	//GetWindowText(hwnd6, add.money, sizeof(add.money));
//	
//	//добавляем её в список
//	//SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)add.FullName);
//	
//		SendMessage(IDC_LIST_LIB1, LB_ADDSTRING, 0, (LPARAM)add.FullName);
//		SendMessage(IDC_LIST_ST1, LB_ADDSTRING, 0, (LPARAM)add.FullName);
//	//и в вектор
//	v.push_back(add);
//}
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//создаём главное окно...
	HWND hwnd;
	MSG msg;
	WNDCLASS w;
	
	memset(&w,0,sizeof(WNDCLASS));
	w.style			= CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc	= WndProc;
	w.hInstance		= hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = TEXT("Library");

	//регистрируем класс окна
	RegisterClass(&w);

	hwnd = CreateWindow(TEXT("Library"),TEXT("Library"), 	WS_OVERLAPPEDWINDOW, 450, 200, 500, 300, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	//добавим кнопки на главное окно
	
	CreateWindow(TEXT("Button"),TEXT("Student"), WS_CHILD|WS_VISIBLE, 	10, 80, 250, 60, hwnd, (HMENU)ID_St, hInstance,NULL);	
	CreateWindow(TEXT("Button"),TEXT("Librarian"), WS_CHILD|WS_VISIBLE, 	10, 10, 250, 60, hwnd, (HMENU)ID_Lib, hInstance,NULL);	
	CreateWindow(TEXT("Button"),TEXT("Exit"), WS_CHILD|WS_VISIBLE, 	10, 150, 250, 60, hwnd, (HMENU)ID_EXIT_MAIN, hInstance,NULL);	
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_CHILD | WS_VISIBLE  | WS_TABSTOP | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL, 270, 10, 70, 50, hwnd,(HMENU)ID_Edit, hInstance, 0);
	
   
	//запускаем цикл обработки сообщений
	while(GetMessage(&msg,NULL,0,0))
	{
		if(hDlgModeless == 0 || !IsDialogMessage(hDlgModeless, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
	 TCHAR pass[50];
//процедура главного окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam,LPARAM lparam)
{	
	
	static HINSTANCE hInstance;
	switch(Message)
	{
	
	case WM_CREATE :
		hInstance =((LPCREATESTRUCT) lparam)->hInstance;

		break;

	case WM_COMMAND:
		if (HIWORD(wparam) == BN_CLICKED) //если была нажата кнопка
        {
			switch (LOWORD(wparam)) 
            { 			
				case ID_St: 
					//создаём 1  модальное окно
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProcModalSt);
					break;				
			       //и это кнопка создания модального окна
				case ID_Lib: {
					TCHAR myStr[50] =TEXT("lib");
					GetDlgItemText(hwnd, ID_Edit,pass, 50);
             //проврка пароля
				//	if (pass == myStr){

					//создаём  2 модальное окно
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, DlgProcModalLib);}
					break;	
				// }
				// else {MessageBox(hwnd, TEXT("Error"), TEXT("Error"), MB_OK);}
				// break;
				case ID_EXIT_MAIN:
					{
					PostQuitMessage(0);
					}
				break;
			}	
	   }
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	}
	return DefWindowProc(hwnd,Message,wparam,lparam);
}

BOOL CALLBACK DlgProcModalSt(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch(iMsg)
	{
		case WM_INITDIALOG :
			SetWindowText(hDlg, TEXT("Student"));
            hstatic_st=GetDlgItem(hDlg, IDC_STATIC_St_out);
			hlist_st=GetDlgItem(hDlg,IDC_LIST_ST1);
			//пробуем заполнить list
	/*		for(int i=0; i<SIZE; i++)
		SendMessage(hlist_st, LB_ADDSTRING, 0, (LPARAM)v[i].FullName);	

	SendMessage(hlist_st, LB_SETCURSEL, 0, 0);
	fillStatic(0);*/

	
		

			return TRUE;
		case WM_CLOSE:
			EndDialog(hDlg, 0);
			break;
		case WM_COMMAND :
		  switch(LOWORD(wParam))
			  {
		  case IDC_Exit_St:
				EndDialog(hDlg, 0);//закрываем окно
				return TRUE;
			}
	      break;
		}
	return FALSE;
}
BOOL CALLBACK DlgProcModalLib(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_INITDIALOG :
			SetWindowText(hDlg, TEXT("Librarian"));//помещаем текст на наше окно
			hstatic_lib=GetDlgItem(hDlg, IDC_STATIC_Lib_Out);
			hlist_lib=GetDlgItem(hDlg, IDC_LIST_LIB1);



			return TRUE;
		case WM_CLOSE:
			EndDialog(hDlg, 0);	//закрываем окно
			break;
		case WM_COMMAND :
	     switch(LOWORD(wParam))
			{
				
			     
				case IDC_Exit:
					EndDialog(hDlg, 0);//закрываем окно
				    return TRUE;
			}
		break;
		}
	return FALSE;
}



