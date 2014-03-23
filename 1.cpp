#include <windows.h>
#include "resource.h"
#include <string>
#include <tchar.h>
#include <vector>
using namespace std;

//����� ������������ ����
HWND hDlgModeless,hEdit1,hstatic, hstatic_st,hstatic_lib,	hlist_lib,	hlist_st;

//������������ ��� ��������� ������� � ������ 
LRESULT ind=LB_ERR; //LB_ERR  � winuser.h ���������� ��� -1//��� ��  ��� LRESULT

//��������� ��������� �������� ���� � ���������� ����������� �����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModalSt(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModalLib(HWND, UINT, WPARAM, LPARAM);

wchar_t str[400];
//��������� ������ ��� �������� ������������ ����������
typedef struct
{
	wchar_t FullName[50];	
	wchar_t Date[50];
	//wchar_t Phone[50]; ��� ������ ���� ��� ������� 
	wchar_t Writer[50];//��� ��� �����
	//wchar_t Address[50];	
	//wchar_t money[50];	
}INFO;


////�� ������ ������������ ������� ������ ������
//vector<INFO> v(info, info+SIZE);

////������ ��� ������ ��������� � ����� ��������� ����� 
////������� ���������� ������� 
//void fillStatic(int index)
//{
////	wcscpy_s(str, TEXT("�����:\n"));						
////	wcscat_s(str, v[index].Address);
//	wcscat_s(str, TEXT("\n���� ��������:\n"));
//	wcscat_s(str, v[index].Date);
////	wcscat_s(str, TEXT("\n�������:\n"));
////	wcscat_s(str, v[index].Phone);
//	wcscat_s(str, TEXT("\n����������� �����:\n"));
//	wcscat_s(str, v[index].Writer);
////	wcscat_s(str, TEXT("\nMoney:\n"));
//	//wcscat_s(str, v[index].money);
//	//SetWindowText(hwndStatic, str);	// ��� ������� ��� ������� 
//	SetWindowText(hstatic_st,str);
//	
//}

//
////������� �������� ��������
//void delElement()
//{
//	//�������� ������ ����������� �������� ������
//	ind=SendMessage(hwndList, LB_GETCURSEL, 0, 0);	
//	//������� ������� �� ������
//	SendMessage(hwndList, LB_DELETESTRING, ind, 0);
//	//������� ������� �� �������
//	v.erase(v.begin()+ind);
//	//������� ������
//	SetWindowText(hwndStatic, TEXT(""));	
//}
//
////������� ���������� ��������
//void addElement()
//{
//	INFO add;	
//	//�������� ���������� � ����������� �������� �� �������� �����
//	GetWindowText(hwnd1, add.FullName, sizeof(add.FullName));
////	GetWindowText(hwnd2, add.Address, sizeof(add.Address));										
	GetWindowText(hwnd3, add.BirthDate, sizeof(add.Date));							
	//GetWindowText(hwnd4, add.Phone, sizeof(add.Phone));					
	GetWindowText(hwnd5, add.Email, sizeof(add.Writer));
	//GetWindowText(hwnd6, add.money, sizeof(add.money));
	
	//��������� � � ������
	//SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)add.FullName);
			SendMessage(IDC_LIST_LIB1, LB_ADDSTRING, 0, (LPARAM)add.FullName);
		SendMessage(IDC_LIST_ST1, LB_ADDSTRING, 0, (LPARAM)add.FullName);
	//� � ������
	v.push_back(add);
}
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//������ ������� ����...
	HWND hwnd;
	MSG msg;
	WNDCLASS w;
	
	memset(&w,0,sizeof(WNDCLASS));
	w.style			= CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc	= WndProc;
	w.hInstance		= hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = TEXT("Library");

	//������������ ����� ����
	RegisterClass(&w);

	hwnd = CreateWindow(TEXT("Library"),TEXT("Library"), 	WS_OVERLAPPEDWINDOW, 450, 200, 500, 300, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	//������� ������ �� ������� ����
	
	CreateWindow(TEXT("Button"),TEXT("Student"), WS_CHILD|WS_VISIBLE, 	10, 80, 250, 60, hwnd, (HMENU)ID_St, hInstance,NULL);	
	CreateWindow(TEXT("Button"),TEXT("Librarian"), WS_CHILD|WS_VISIBLE, 	10, 10, 250, 60, hwnd, (HMENU)ID_Lib, hInstance,NULL);	
	CreateWindow(TEXT("Button"),TEXT("Exit"), WS_CHILD|WS_VISIBLE, 	10, 150, 250, 60, hwnd, (HMENU)ID_EXIT_MAIN, hInstance,NULL);	
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_CHILD | WS_VISIBLE  | WS_TABSTOP | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL, 270, 10, 70, 50, hwnd,(HMENU)ID_Edit, hInstance, 0);
	
   
	//��������� ���� ��������� ���������
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
//��������� �������� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam,LPARAM lparam)
{	
	
	static HINSTANCE hInstance;
	switch(Message)
	{
	
	case WM_CREATE :
		hInstance =((LPCREATESTRUCT) lparam)->hInstance;

		break;

	case WM_COMMAND:
		if (HIWORD(wparam) == BN_CLICKED) //���� ���� ������ ������
        {
			switch (LOWORD(wparam)) 
            { 			
				case ID_St: 
					//������ 1  ��������� ����
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProcModalSt);
					break;				
			       //� ��� ������ �������� ���������� ����
				case ID_Lib: {
					TCHAR myStr[50] =TEXT("lib");
					GetDlgItemText(hwnd, ID_Edit,pass, 50);
             //������� ������
				//	if (pass == myStr){

					//������  2 ��������� ����
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
			//������� ��������� list
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
				EndDialog(hDlg, 0);//��������� ����
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
			SetWindowText(hDlg, TEXT("Librarian"));//�������� ����� �� ���� ����
			hstatic_lib=GetDlgItem(hDlg, IDC_STATIC_Lib_Out);
			hlist_lib=GetDlgItem(hDlg, IDC_LIST_LIB1);



			return TRUE;
		case WM_CLOSE:
			EndDialog(hDlg, 0);	//��������� ����
			break;
		case WM_COMMAND :
	     switch(LOWORD(wParam))
			{
				
			     
				case IDC_Exit:
					EndDialog(hDlg, 0);//��������� ����
				    return TRUE;
			}
		break;
		}
	return FALSE;
}



