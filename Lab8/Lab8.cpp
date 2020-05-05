#include "stdafx.h"
#include "Lab8.h"
#include "windows.h"
#include <vector>
#include <algorithm>

#define MAX_LOADSTRING 200
#define ID_DRAW 100
#define ID_CLEAR 101

using namespace std;

//����������� - ��������� �� �������� �������� ������������ �������(�������� ��� ������ ���-�������)
//_T() - �������� ������ Unicode �� ����� ����������


// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);	//������� ����������� ����(����� int)
BOOL                InitInstance(HINSTANCE, int);			//������������� ����
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	//�������� ���� (lresult - �������� ������� ��������� long)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		//��� ����� ��������� � int, � ���������

//�������� �������
int APIENTRY wWinMain(HINSTANCE hInstance,				//������� ����������
					  HINSTANCE hPrevInstance,			//���������� ���������� (� ����������� ������ ����)
                      LPWSTR    lpCmdLine,				//��������� ������
                      int       mode)					//����� �����������
{
    UNREFERENCED_PARAMETER(hPrevInstance);				//���� ���������� �� �������, ��� ���������� �� ������������
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB_8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, mode))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB_8));		//�������� ������� ������� ������
	//��������� ��� �������� ���������
    MSG msg;				

    // ���� ��������� ���������(��������� �� ���������, ����(���), min �������� ����������, max):
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))			//�� ������ �� ������� �������? ���� ��, �� ������� � WndProc
        {
            TranslateMessage(&msg);			//���������� ����� ������� �������
            DispatchMessage(&msg);			//�������� ��������� ������� WndProc
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
    WNDCLASSEXW wcex;					//����� ����
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// ����� ����(�������������� ���������� ��� ��������� ������ � ������)
    wcex.lpfnWndProc    = WndProc;					//��� ������� ��� ��������� ���������
    wcex.cbClsExtra     = 0;						//��� ������ �����
    wcex.cbWndExtra     = 0;						//��� ������ ����
    wcex.hInstance      = hInstance;				//������� ����������
    wcex.hIcon          = 0;	//������
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);							//������
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);					//���������� ���� ������
    wcex.lpszMenuName   = NULL;								//����
    wcex.lpszClassName  = szWindowClass;										//��� ������ ����
    wcex.hIconSm        = 0;	//���������� ��������� ������

    return RegisterClassExW(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int mode)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION|WS_MINIMIZEBOX|WS_OVERLAPPED|WS_SYSMENU,
      300, 120, 800, 500, nullptr, nullptr, hInstance, nullptr);

   
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, mode);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)	
//
//  ����������:  ������������ ��������� � ������� ����.
//
//	WM_CREATE - �������� ����
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//	WM_SIZE - ������������ ��� ��������� ������� ����
//	WM_DRAWITEM - ��������� ��� ������������� ����������� ��������
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hBtnDraw, hBtnClear;
	static bool picture = false;
	PAINTSTRUCT ps;
	HDC hdc;
	DRAWITEMSTRUCT* lpDrawItem;
	static HBRUSH sandBrush, pinkBrush, redBrush, yellowBrush, blackBrush, greenBrush, stoneBrush, purpleStoneBrush, backBrush, blueBrush, drawBrush, clearBrush; 
	switch (message)
	{
		case WM_CREATE:
			backBrush = CreateSolidBrush(RGB(170, 220, 255));
			blueBrush = CreateSolidBrush(RGB(50, 60, 200));
			purpleStoneBrush = CreateSolidBrush(RGB(93, 71, 139));
			sandBrush = CreateSolidBrush(RGB(184, 134, 11));
			pinkBrush = CreateSolidBrush(RGB(218, 112, 214));
			yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
			blackBrush = CreateSolidBrush(RGB(0, 0, 0));
			redBrush = CreateSolidBrush(RGB(210, 0, 0));
			greenBrush = CreateSolidBrush(RGB(0, 139, 0));
			stoneBrush = CreateSolidBrush(RGB(139, 126, 102));
			hBtnDraw = CreateWindowW(L"Button", L"��������", WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 710, 20, 60, 60, hWnd, (HMENU)ID_DRAW, NULL, NULL);
			hBtnClear = CreateWindowA("Button", "��������", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 710, 90, 60, 60, hWnd, (HMENU)ID_CLEAR, NULL, NULL);
			break;

		case WM_PAINT:
			if (picture) {
				hdc = BeginPaint(hWnd, &ps);
				SelectObject(hdc, purpleStoneBrush);
				Rectangle(hdc, 0, 0, 1000, 700);

				SelectObject(hdc, yellowBrush);
				Ellipse(hdc, 0, 150, 150, 0);
				
				SelectObject(hdc, greenBrush);
				Rectangle(hdc, 0, 400, 1000, 500);

				SelectObject(hdc, blackBrush);
				Rectangle(hdc, 100, 300, 300, 400);

				SelectObject(hdc, yellowBrush);
				Rectangle(hdc, 105, 305, 125, 325);
				SelectObject(hdc, yellowBrush);
				Rectangle(hdc, 125, 305, 145, 325);
				SelectObject(hdc, yellowBrush);

				SelectObject(hdc, yellowBrush);
				Rectangle(hdc, 105, 325, 125, 345);
				SelectObject(hdc, yellowBrush);
				Rectangle(hdc, 125, 325, 145, 345);
				SelectObject(hdc, yellowBrush);

				SelectObject(hdc, stoneBrush);
				Rectangle(hdc, 200, 360, 225, 400);

				EndPaint(hWnd, &ps);

			}
			else {
				hdc = BeginPaint(hWnd, &ps);
				SelectObject(hdc, (HBRUSH)(COLOR_WINDOW + 1));
				Rectangle(hdc, 0, 0, 800, 500);
				EndPaint(hWnd, &ps);
			}
			break;

		case WM_DRAWITEM:
			lpDrawItem = (DRAWITEMSTRUCT*)lParam;
			hdc = (*lpDrawItem).hDC;
			drawBrush = CreateSolidBrush(RGB(255, 130, 171));
			clearBrush = CreateSolidBrush(RGB(178, 223, 238));
			if (LOWORD(wParam) == ID_DRAW) {
				SelectObject(hdc, drawBrush);
				Rectangle(hdc, 0, 0, 60, 60);
				SelectObject(hdc, clearBrush);
				Ellipse(hdc, 20, 20, 40, 40);
			}
			else if (LOWORD(wParam) == ID_CLEAR){
				POINT points[3] = { {20, 40}, {30, 30}, {40, 40} };
				SelectObject(hdc, clearBrush);
				Rectangle(hdc, 0, 0, 60, 60);
				SelectObject(hdc, drawBrush);
				Ellipse(hdc, 20, 20, 40, 40);
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_DRAW:
					picture = true;
					InvalidateRect(hWnd, NULL, false);
					break;
				case ID_CLEAR:
					picture = false;
					InvalidateRect(hWnd, NULL, false);
					break;
			}
			break;
		case WM_DESTROY:
			DeleteObject(backBrush);
			DeleteObject(pinkBrush);
			DeleteObject(yellowBrush);
			DeleteObject(sandBrush);
			DeleteObject(greenBrush);
			DeleteObject(blackBrush);
			DeleteObject(stoneBrush);
			DeleteObject(purpleStoneBrush);
			DeleteObject(drawBrush);
			DeleteObject(clearBrush);
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		return 0;
}

