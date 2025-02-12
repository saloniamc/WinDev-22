//header files
#include<Windows.h>
#include "Window.h" 

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declaration


//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
	
	//CODE
	//WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//Creating the window

	hwnd = CreateWindow(
		szAppName,
		TEXT("SSB:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Show Window
	ShowWindow(hwnd, iCmdShow);

	//Update Window
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hBrush;
	static int iPaintFlag = 0;

	//CODE
	switch (iMsg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'K':
		case 'k':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'W':
		case 'w':
			iPaintFlag = 8;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		default:
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
		}
		else if (iPaintFlag == 2) {
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (iPaintFlag == 3) {
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (iPaintFlag == 4) {
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iPaintFlag == 5) {
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iPaintFlag == 6) {
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iPaintFlag == 7) {
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
		}
		else if (iPaintFlag == 8) {
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
		}
		else {
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
		}
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

