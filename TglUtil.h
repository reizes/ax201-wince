#ifndef __TGL_UTIL__
#define __TGL_UTIL__

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

TEST_API void Tgl_ReleasePath(int** Path);
TEST_API int** Tgl_CreateLinePath(int x1,int y1,int x2,int y2,int Step);
TEST_API int** Tgl_CreateSplinePath(int *x, int *y, int Num,int Step);

#endif