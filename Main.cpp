#include "resource.h"
#include "Main.h"

Tgl *TglStruct;
TglSurface *BgMainSurface;
TglSurface *BgFar[2],*BgMiddleL[2],*BgMiddleR[2],*BgNearL[2],*BgNearR[2];
TglSurface *Ship[3],*ShipMain,*OutShip;
int ScrollPos=0;
int ShipPosX=108,ShipPosY=300;

void InitGame(HINSTANCE hInstance,HWND hWnd)
{
	RECT Rect1={83,0,155,319};
	RECT Rect2={40,0,82,319};
	RECT Rect3={156,0,198,319};
	RECT Rect4={0,0,39,319};
	RECT Rect5={199,0,239,319};

	TglStruct=Tgl_Open(hWnd);
	// Back Image Loading
	BgMainSurface=Tgl_LoadGIFSurface(hInstance,IDR_BG,TglStruct);
	BgFar[0]=Tgl_CreateSurfaceFrom(Rect1,BgMainSurface);
	BgFar[1]=Tgl_CreateSurfaceFrom(Rect1,BgMainSurface);
	BgMiddleL[0]=Tgl_CreateSurfaceFrom(Rect2,BgMainSurface);
	BgMiddleL[1]=Tgl_CreateSurfaceFrom(Rect2,BgMainSurface);
	BgMiddleR[0]=Tgl_CreateSurfaceFrom(Rect3,BgMainSurface);
	BgMiddleR[1]=Tgl_CreateSurfaceFrom(Rect3,BgMainSurface);
	BgNearL[0]=Tgl_CreateSurfaceFrom(Rect4,BgMainSurface);
	BgNearL[1]=Tgl_CreateSurfaceFrom(Rect4,BgMainSurface);
	BgNearR[0]=Tgl_CreateSurfaceFrom(Rect5,BgMainSurface);
	BgNearR[1]=Tgl_CreateSurfaceFrom(Rect5,BgMainSurface);
	int i;
	for (i=0;i<2;i++)
	{
		BgFar[i]->x=83;
		BgMiddleL[i]->x=40;
		BgMiddleR[i]->x=156;
		BgNearL[i]->x=0;
		BgNearR[i]->x=199;
	}
	// Ship Image Loading
	Rect1.left=0; Rect1.top=0;
	Rect1.right=25; Rect1.bottom=19;
	ShipMain=Tgl_LoadGIFSurface(hInstance,IDR_SHIP,TglStruct);
	OutShip=Ship[0]=Tgl_CreateSurfaceFrom(Rect1,ShipMain);
	Rect1.left=31; 
	Rect1.right=47;
	Ship[1]=Tgl_CreateSurfaceFrom(Rect1,ShipMain);
	Rect1.left=54; 
	Rect1.right=70;
	Ship[2]=Tgl_CreateSurfaceFrom(Rect1,ShipMain);
	for (i=0;i<3;i++)
	{
		Tgl_SetTransColor(RGB(24,24,24),Ship[i],TglStruct);
		Tgl_EnableTrans(TRUE,Ship[i]);
	}
}

void OnCreate()
{
	Tgl_ReleaseSurface(BgMainSurface);
	Tgl_ReleaseSurface(ShipMain);
}

void Draw()
{
			int i;
			Tgl_BeginDraw(TglStruct);
			for (i=0;i<2;i++)
			{
				Tgl_DrawSurfaceToBack(TglStruct,BgFar[i]);
				Tgl_DrawSurfaceToBack(TglStruct,BgMiddleL[i]);
				Tgl_DrawSurfaceToBack(TglStruct,BgMiddleR[i]);
				Tgl_DrawSurfaceToBack(TglStruct,BgNearL[i]);
				Tgl_DrawSurfaceToBack(TglStruct,BgNearR[i]);
				OutShip->x=ShipPosX; OutShip->y=ShipPosY;
				Tgl_DrawSurfaceToBack(TglStruct,OutShip);
			}
			Tgl_Flip(TglStruct);
			Tgl_EndDraw();
}

void ExitGame()
{
	int i;
	for (i=0;i<2;i++)
	{
		Tgl_ReleaseSurface(BgFar[i]);
		Tgl_ReleaseSurface(BgMiddleL[i]);
		Tgl_ReleaseSurface(BgMiddleR[i]);
		Tgl_ReleaseSurface(BgNearL[i]);
		Tgl_ReleaseSurface(BgNearR[i]);
	}
	Tgl_Close(TglStruct);
}

void KeyDown(DWORD Code)
{
	if (Code == (DWORD)TglStruct->gxkl.vkStart) 
	{
		SendMessage(TglStruct->hWnd, WM_CLOSE, 0, 0);
		return;
	}
	if (Code == (DWORD)TglStruct->gxkl.vkLeft) 
	{
		OutShip=Ship[2];
		ShipPosX-=5;
		if (ShipPosX<0) ShipPosX=0;
	}
	if (Code == (DWORD)TglStruct->gxkl.vkRight) 
	{
		OutShip=Ship[1];
		ShipPosX+=5;
		if (ShipPosX>224) ShipPosX=224;
	}
	if (Code == (DWORD)TglStruct->gxkl.vkUp) 
	{
		ShipPosY-=5;
		if (ShipPosY<0) ShipPosY=0;
	}
	if (Code == (DWORD)TglStruct->gxkl.vkDown) 
	{
		ShipPosY+=5;
		if (ShipPosY>300) ShipPosY=300;
	}
}

void KeyUp(DWORD Code)
{
	if ((Code == (DWORD)TglStruct->gxkl.vkLeft)||(Code == (DWORD)TglStruct->gxkl.vkRight)||(Code == (DWORD)TglStruct->gxkl.vkUp)||(Code == (DWORD)TglStruct->gxkl.vkDown))
		OutShip=Ship[0];
}
void Scroll()
{
	BgFar[0]->y=(BgFar[0]->y+1)%320;
	BgFar[1]->y=BgFar[0]->y-320;
	BgMiddleL[0]->y=(BgMiddleL[0]->y+5)%320;
	BgMiddleL[1]->y=BgMiddleL[0]->y-320;
	BgMiddleR[0]->y=(BgMiddleR[0]->y+5)%320;
	BgMiddleR[1]->y=BgMiddleR[0]->y-320;
	BgNearL[0]->y=(BgNearL[0]->y+10)%320;
	BgNearL[1]->y=BgNearL[0]->y-320;
	BgNearR[0]->y=(BgNearR[0]->y+10)%320;
	BgNearR[1]->y=BgNearR[0]->y-320;
}

void CALLBACK TimerProc(HWND hwnd,UINT nMsg,UINT idEvent, DWORD dwTime)
{
	switch(idEvent)
	{
	case 100 :
		Draw();
		break;
	case 101 :
		Scroll();
	}
}