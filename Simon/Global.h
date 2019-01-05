
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12
#define GL_KEY_BUFFER_SIZE	1024

extern struct Box
{
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}
	float x, y;   
	float w, h;   
	float vx, vy;    
};

extern int Game_CurForm;
extern int Game_NextForm;

extern bool			Game_IsInitedDX;		    
extern int			Game_Depth;		      
extern char*		Game_Name;		     
extern int			Game_FrameRate;		   
extern int			Game_ColorMode;		    
extern bool			Game_IsFullScreen;	    
extern D3DFORMAT	Game_BackBufferFormat;     

extern bool			Game_HasBackgroundSound;		     
extern bool			Game_HasEffectSound;	     

extern int			Game_MapWidth;			        
extern int			Game_MapHeight;			        

extern int			Game_ScreenWidth;			   
extern int			Game_ScreenHeight;			   
extern int			SIZE_384;

extern int			Game_MaxSize;
extern int			Game_MinSize;

extern int			State;
extern int			ReadFileNew;
extern int			PlayingMusic;
extern int			AutoFit;
extern int			Floor;
extern int			OpeningTheGate;
extern bool			IsOpenTheGate;
extern int			TestGame;
extern int			DrawInvisibleObj;
extern int			ShowBox;
extern bool			Start_Test_Jump;
//Cont Object Game
extern int BAT;
extern int GHOUL;
extern int PANTHER;
extern int FISH_MAN;
extern int AXE_KNIGHT;
extern int SPEAR_KNIGHT;
extern int MEDUSA_HEAD;
extern int BONE_TOWER;
extern int GHOST;
extern int TORCH;
extern int CANDLE;
extern int BRICK;
extern int STAIR;
extern int STAIR2;
extern int UP_STAIR_OBJECT;
extern int DOWN_STAIR_OBJECT;
extern int SPIKE_TRAP;
extern int FLYING_BRICK;
extern int DOOR;
extern int INVISIBLE_OBJECT;
extern int WATER_OBJECT;
extern int RIGHT_OBJECT;
extern int BOSS_BAT;
extern int BOSS_MEDUSA;
extern int SIMON_OBJECT;
//Const Weapon
extern int SWORD;
extern int AXE;
extern int BOTTLE;
extern int BUMERAN;
extern int FIRE_BALL;
extern int MORNING_STAR;
extern int SNAKE_WEAPON;
//Const Collection Item
extern int SWORD_ITEM;
extern int AXE_ITEM;
extern int BOTTLE_ITEM;
extern int BUMERAN_ITEM;
extern int STOPWATCH_ITEM;
extern int MORNINGSTAR_ITEM;
extern int BALL_ITEM;
extern int BIGHEART_ITEM;
extern int CROSS_ITEM;
extern int HEART_ITEM;
extern int SHOT2_ITEM;
extern int SHOT3_ITEM;
extern int MONEYBAG_ITEM;
extern int PORKCHOP_ITEM;
extern int POTION_ITEM;
extern int POINT_MONEYBAT_ITEM;
extern int LEFT;
extern int RIGHT;

extern int IS_ACTION;
extern int NO_ACTION;

extern int NO_COLLIDE;
extern int COLLIDE_LEFT;
extern int COLLIDE_RIGHT;
extern int COLLIDE_BOTTOM;
extern int COLLIDE_TOP;
extern int IS_COLLIDE;

extern int STEP_0;
extern int STEP_1;
extern int STEP_2;
extern int STEP_3;

extern int STATE_2_X1;
extern int STATE_2_X2;
extern int STATE_3_X1;

extern int TIME_ANI_50;
extern int TIME_ANI_70;
extern int TIME_ANI_100;
extern int TIME_ANI_150;
extern int TIME_ANI_600;

extern int number_0;
extern int num_1;
extern int num_2;
extern int num_3;
extern int num_4;
extern int number_5;
extern int num_6;
extern int num_7;
extern int num_10;
extern int num_16;
extern int num_18;
extern int num_20;
extern int num_22;
extern int num_30;
extern int num_40;
extern int number_50;
extern int num_60;
extern int num_70;
extern int num_80;
extern int num_100;
extern int num_120;
extern int num_140;
extern int num_255;
extern int num_445;
extern int num_900;
extern int num_1000;
extern int num_3100;
extern int num_3071;
extern int num_4100;
extern int num_4098;
extern int num_1536;
extern int num_4096;
extern RECT			Game_WindowSize;			   


extern HINSTANCE					Game_hInstance;		     
extern HWND							Game_hWnd;			     

extern LPDIRECT3D9					Game_DirectX;			 
extern LPDIRECT3DDEVICE9			Game_Device;			 
extern LPDIRECT3DSURFACE9			Game_BackBuffer;		

extern LPDIRECTINPUT8				Game_DirectInput;		            
extern LPDIRECTINPUTDEVICE8			Game_KeyBoard;			    
extern LPD3DXSPRITE					Game_SpriteHandler;	    

extern LPDIRECT3DSURFACE9			Surface;

void GLTrace(char* format, ...);

void GLMessage(char* text);

void GLTitle(char* text);

#endif