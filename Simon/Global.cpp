
#include "Global.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

int Game_CurForm;
int Game_NextForm;

bool		Game_IsInitedDX = false;
int			Game_Depth;
char*		Game_Name = "CastleVania";
int			Game_FrameRate = 60;
int			Game_ColorMode;
bool		Game_IsFullScreen = false;
D3DFORMAT	Game_BackBufferFormat;

bool		Game_HasBackgroundSound = true;
bool		Game_HasEffectSound = true;

int			Game_MapWidth;
int			Game_MapHeight;

int			Game_MaxSize;
int			Game_MinSize;

RECT		Game_WindowSize;
int			Game_ScreenWidth = 512; 			
int			Game_ScreenHeight = 448; 	
int			SIZE_384 = 384;
int			State = -1;
int			ShowBox = 0;
int			ReadFileNew = 1;
int			PlayingMusic = 0;
int			AutoFit = 0;
bool		IsOpenTheGate = false;
int 		TestGame = 1;
int			Floor = 1;

int			DrawInvisibleObj = 0;
int			OpeningTheGate = 0;
bool		Start_Test_Jump = 0;

//Enemies
int	BAT = 0;
int	GHOUL = 1;
int PANTHER = 2;
int FISH_MAN = 3;
int TORCH = 10;
int CANDLE = 11;
//Ground
int BRICK = 12;
int STAIR = 13;
int STAIR2 = 14;
//Object
int UP_STAIR_OBJECT = 15;
int DOWN_STAIR_OBJECT = 16;
int DOOR = 20;
int INVISIBLE_OBJECT = 21;
int	WATER_OBJECT = 23;
//Boss
int BOSS_BAT = 26;
//Simon
int SIMON_OBJECT = 40;
//CONST Type WEAPON;
int SWORD = 1;
int AXE = 3;
int BOTTLE = 2;
int BUMERAN = 4;
int FIRE_BALL = 5;
int MORNING_STAR = 0;
 //Const Collection Item
int SWORD_ITEM = 4;
int AXE_ITEM = 7;
int BOTTLE_ITEM = 9;
int BUMERAN_ITEM = 8;
int STOPWATCH_ITEM = 5;
int MORNINGSTAR_ITEM = 3;
int BALL_ITEM = 13;
int BIGHEART_ITEM = 1;
int CROSS_ITEM = 6;
int HEART_ITEM = 0;
int SHOT2_ITEM = 11;
int SHOT3_ITEM = 12;
int MONEYBAG_ITEM = 2;
int PORKCHOP_ITEM = 10;
int POTION_ITEM = 14;
int POINT_MONEYBAT_ITEM = 20;
//Cont inGame
int LEFT = -1;
int RIGHT = 1;

int IS_ACTION = 1;
int NO_ACTION = 0;

int NO_COLLIDE = 0;
int COLLIDE_LEFT = 1;
int COLLIDE_RIGHT = 2;
int COLLIDE_BOTTOM = 3;
int COLLIDE_TOP = 4;
int IS_COLLIDE = 5;

int STEP_0 = 0;
int STEP_1 = 1;
int STEP_2 = 2;
int STEP_3 = 3;

//Toa do Door
int STATE_2_X1 = 3100;
int STATE_2_X2 = 4100;
int STATE_3_X1 = 1536;

//Time ANIMATION
int TIME_ANI_50 = 50;
int TIME_ANI_70 = 70;
int TIME_ANI_100 = 100;
int TIME_ANI_150 = 150;
int TIME_ANI_600 = 600;

int number_0 = 0;
int num_1 = 1;
int num_2 = 2;
int num_3 = 3;
int num_4 = 4;
int number_5 = 5;
int num_6 = 6;
int num_7 = 7;
int num_10 = 10;
int num_16 = 16;
int num_18 = 18;
int num_20 = 20;
int num_22 = 22;
int num_30 = 30;
int num_40 = 40;
int number_50 = 50;
int num_70 = 70;
int num_60 = 60;
int num_80 = 80;
int num_100 = 100;
int num_120 = 120;
int num_140 = 140;
int num_255 = 255;
int num_445 = 445;
int num_900 = 900;
int num_1000 = 1000; 
int num_3100 = 3100;
int num_3071 = 3071;
int num_4100 = 4100;
int num_4098 = 4098;
int num_1536 = 1536;
int num_4096 = 4096;

HINSTANCE					Game_hInstance;		     
HWND						Game_hWnd;				     

LPDIRECT3D9					Game_DirectX;
LPDIRECT3DDEVICE9			Game_Device;
LPDIRECT3DSURFACE9			Game_BackBuffer;

LPDIRECTINPUT8				Game_DirectInput;		            
LPDIRECTINPUTDEVICE8		Game_KeyBoard;			    
LPD3DXSPRITE				Game_SpriteHandler;	    

LPDIRECT3DSURFACE9			Back_buffer = NULL;
LPDIRECT3DSURFACE9			Surface = NULL;

void GLTrace(char* format, ...)
{	
	char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
	int _traceNum = 1;

	if (!_traceNum) return;

	FILE *f = stderr;
	if (_traceFile!=NULL)
	{
		if (fopen_s(&f, _traceFile,"a")!=0) 
		{
			fprintf(stderr,"WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
			return;
		}
	}
	va_list ap;
	va_start(ap, format);
	fprintf(f, format, ap);
	va_end(ap);
	fprintf(f,"\n");
	if (_traceFile != NULL) fclose(f);
}

void GLMessage(char* text)
{
	MessageBox(Game_hWnd, text, "Sample TH", MB_OK);
}

void GLTitle(char* text){
	SetWindowText(Game_hWnd, text);
}