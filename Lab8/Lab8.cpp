#include "stdafx.h"
#include "Lab8.h"
#include "windows.h"
#include <vector>
#include <algorithm>

#define MAX_LOADSTRING 200
#define ID_DRAW 100
#define ID_CLEAR 101

using namespace std;

//Дескприптор - описатель ля описания объектов операционной системы(примерно как индекс хэш-таблицы)
//_T() - создание строки Unicode на этапе компиляции


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);	//функция регистрации окна(почти int)
BOOL                InitInstance(HINSTANCE, int);			//инициализация окна
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	//прототип окна (lresult - значение оконной процедуры long)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		//тип может содержать и int, и указатель

//головная функция
int APIENTRY wWinMain(HINSTANCE hInstance,				//текущее приложение
					  HINSTANCE hPrevInstance,			//предыдущее приложение (в современных всегда ноль)
                      LPWSTR    lpCmdLine,				//командная строка
                      int       mode)					//режим отображения
{
    UNREFERENCED_PARAMETER(hPrevInstance);				//дабы компилятор не ругался, что переменные не используются
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB_8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, mode))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB_8));		//загрузка таблицы горячих клавиш
	//структура для хранения сообщений
    MSG msg;				

    // Цикл основного сообщения(указатель на структуру, окна(все), min значение соообщения, max):
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))			//не нажата ли горячая клавиша? Если да, то ступаем к WndProc
        {
            TranslateMessage(&msg);			//трансляция кодов нажатой клавиши
            DispatchMessage(&msg);			//посылает сообщение функции WndProc
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
    WNDCLASSEXW wcex;					//класс окна
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// Стиль окна(атвоматическая перерисова при изменении высоты и ширины)
    wcex.lpfnWndProc    = WndProc;					//Имя функции для обработки сообщений
    wcex.cbClsExtra     = 0;						//доп данные класс
    wcex.cbWndExtra     = 0;						//доп данные окна
    wcex.hInstance      = hInstance;				//текущее приложение
    wcex.hIcon          = 0;	//иконка
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);							//курсор
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);					//заполнение окна цветом
    wcex.lpszMenuName   = NULL;								//меню
    wcex.lpszClassName  = szWindowClass;										//имя класса окна
    wcex.hIconSm        = 0;	//дескриптор маленькой иконки

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int mode)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)	
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//	WM_CREATE - создание окна
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//	WM_SIZE - генерируется при изменении размера окна
//	WM_DRAWITEM - сообщение при необходимости перерисовки элемента
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
			hBtnDraw = CreateWindowW(L"Button", L"Добавить", WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 710, 20, 60, 60, hWnd, (HMENU)ID_DRAW, NULL, NULL);
			hBtnClear = CreateWindowA("Button", "Очистить", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 710, 90, 60, 60, hWnd, (HMENU)ID_CLEAR, NULL, NULL);
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

