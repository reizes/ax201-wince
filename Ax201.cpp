
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include "resource.h"
#include "Main.h"

//
// Forward declarations.
//

ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
// Code Body
//

int WINAPI WinMain(	HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine,int       nCmdShow)
{
	MSG msg;

	if (!InitInstance (hInstance, nCmdShow)) return FALSE;

	// Main message loop.

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS	wc;
    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= NULL;
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;
	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd;
	TCHAR	szTitle[] = L"TglCESample";			// The title bar text
	TCHAR	szWindowClass[] = L"TglCESample";	// The window class name

	// IMPORTANT:  see if this app is already running.  If so just bring
	// it to the front and quit.  All CE apps need to do this.
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {SetForegroundWindow ((HWND) (((DWORD)hWnd) | 0x01));return 0;} 
	MyRegisterClass(hInstance, szWindowClass);

	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,	0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow); UpdateWindow(hWnd);

	InitGame(hInstance,hWnd);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	short vkKey;

	switch (message) {
		case WM_CREATE:
			OnCreate();
			break;

		case WM_TIMER:
			break;

		case WM_ACTIVATE:
			break;

		case WM_KILLFOCUS:
			Tgl_Suspend();
			break;


		case WM_SETFOCUS:
			Tgl_Resume();
			break;

		// If your app can only draw directly to the screen then you need to make
		// sure it is frontmost before drawing.

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			Draw();
			break;

		case WM_KEYDOWN:
			vkKey = (short)wParam;
			KeyDown((DWORD)vkKey);
			break;
		case WM_KEYUP:
			vkKey = (short)wParam;
			KeyUp((DWORD)vkKey);
			break;
		case WM_LBUTTONDOWN:
			SetTimer(hWnd, 101, 100,TimerProc);
			SetTimer(hWnd, 100, 30,TimerProc);
			break;
		case WM_DESTROY:
			KillTimer(hWnd,101);
			ExitGame();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

