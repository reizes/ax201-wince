#ifndef __TGL_GIF__
#define	__TGL_GIF__

#include "Windows.h"

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

typedef struct {
	unsigned short cxWidth,cyHeight;
	RGBQUAD rgbq[256];
	BYTE *lpImage;
} TglGIF;

TEST_API TglGIF* Tgl_LoadGIFResource(HINSTANCE hInst, int resID );
TEST_API void    Tgl_ReleaseGIFResource(TglGIF *Gif);

#endif