
#ifndef __TGL_CE_LIB__
#define __TGL_CE_LIB__
#include "Windows.h"
#include "gx.h"

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

typedef struct {
	BYTE *lpImageSrc;
	DWORD  cxWidth,cyHeight;
	RECT ViewRect;
	int  x,y;
	BYTE TransColor[3];
	BOOL TransFlag;
	int  cbxPitch;
	int  cbyPitch;
} TglSurface;

typedef struct {
	HWND hWnd;	// MainWindow
	GXDisplayProperties gxdp;	// GX struct (Display Properties)
	GXKeyList gxkl;				// GX struct (Key List)
	BYTE *lpBackBuffer;
	BYTE *lpDisplay;
} Tgl;


TEST_API Tgl* Tgl_Open(HWND hWnd);
TEST_API void Tgl_Close(Tgl* TglStruct);
TEST_API void Tgl_Suspend() ;
TEST_API void Tgl_Resume();
TEST_API void Tgl_BeginDraw(Tgl* TglStruct);
TEST_API void Tgl_EndDraw();
TEST_API void Tgl_Flip(Tgl* TglStruct);
TEST_API void Tgl_DrawSurfaceToBack(Tgl* TglStruct, TglSurface *Surface);
TEST_API void Tgl_DrawSurfaceToDisplay(Tgl* TglStruct, TglSurface *Surface);
TEST_API TglSurface* Tgl_CreateSurface(int w,int h,Tgl* TglStruct);
TEST_API TglSurface* Tgl_CreateSurfaceFrom(RECT &pRect,TglSurface *ISurface);
TEST_API void Tgl_EnableTrans(BOOL Flag,TglSurface *Surface);
TEST_API void Tgl_SetTransColor(COLORREF Color,TglSurface* Surface,Tgl* TglStruct);
TEST_API void Tgl_ReleaseSurface(TglSurface *Surface);
TEST_API TglSurface* Tgl_LoadGIFSurface(HINSTANCE hInst, int resID,Tgl* TglStruct);
#endif