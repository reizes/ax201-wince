#include "TglCE.h"
#include "TglUtil.h"

void InitGame(HINSTANCE hInstance,HWND hWnd);
void OnCreate();
void Draw();
void ExitGame();
void KeyDown(DWORD Code);
void KeyUp(DWORD Code);
void Scroll();
void CALLBACK TimerProc(HWND hwnd,UINT nMsg,UINT idEvent, DWORD dwTime);