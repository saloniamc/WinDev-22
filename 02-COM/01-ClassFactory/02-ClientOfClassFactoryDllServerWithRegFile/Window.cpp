//header files
#include<Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"
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
	HRESULT hR;

	//COM library initialization
	hR = CoInitialize(NULL);
	if (FAILED(hR))
	{
		MessageBox(NULL, TEXT("Com Initialization Failed"), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	
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

	//Com Uninitialization
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declaration
	ISum* pISum = NULL;
	ISubstract* pISubstract = NULL;
	int n1, n2, sum, substract;
	TCHAR str[255];
	HRESULT hR;

	//CODE
	switch (iMsg)
	{
	case WM_CREATE:
		hR = CoCreateInstance(CLSID_SumSubstract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hR))
		{
			MessageBox(hwnd, TEXT("ISum Cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 55;
		n2 = 45;
		pISum->SumOfTwoIntegers(n1, n2, &sum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);
		pISum->QueryInterface(IID_ISubstract, (void**)&pISubstract);
		pISubstract->SubstractionOfTwoIntegers(n1, n2, &substract);
		wsprintf(str, TEXT("Substraction of %d and %d is %d"), n1, n2, substract);
		MessageBox(hwnd, str, TEXT("Substraction"), MB_OK);

		//Safe Release
		if (pISubstract)
		{
			pISubstract->Release();
			pISubstract = NULL;
		}
		if (pISum)
		{
			pISum->Release();
			pISum = NULL;
		}
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
