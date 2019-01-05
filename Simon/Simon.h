#ifndef _SIMON_H_
#define _SIMON_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define SIMON_IMAGE "Resources/simon.png"
#define SIMON_IMAGE_TR "Resources/simon_trans.png"
#define SIMON_TREND 1
#define SIMON_FRAME 70
#define SIMON_STOP 0
#define SIMON_SIT 4
#define SIMON_STOP 0
#define SIMON_ATK 5
#define SIMON_SITATK 15
#define SIMON_HURT 8

#define SIMON_X 50
#define SIMON_Y 90

#define SIMON_VX 5.0f
#define SIMON_VX_STAIR 1.5	
#define SIMON_VY_STAIR 1.5
#define SIMON_VJUMP 12
#define SIMON_GRAVITY 1
#define SIMON_FALL 180
#define SIMON_VX_DAMAGED 150
#define SIMON_VY_DAMAGED 450

class Simon : public Object
{
	bool IsOnStair;
	GameSprite * SimonDeath;
	float SIMON_vx;
	int HTrend;
	GameTexture *TrSize;
	GameSprite *TrObjectSprite;
	int test = 0;

public:
	bool IsUp, IsDown;
	bool AutoGo;
	int stairtrend;
	int x_upstair;
	int y_upstair;
	int x_downstair;
	int y_downstair;
	int ResetSimon;
	float BonusVx;
	int Invisible;
	int Prevent;
	float Vx_Hurt;

	Simon(float Vx = SIMON_VX, int iG = 0, float x = SIMON_X, float y = SIMON_Y, int Trend = SIMON_TREND);
	~Simon();
	int WaitingCount;   
	int IntoCastle(int t);
	virtual void Sit();
	virtual void StandUp();
	virtual void Jump();
	virtual void Fall();
	virtual void Go();
	virtual void Stop();
	virtual void StopFall(float y);
	virtual void Attack(Weapon *weapon = NULL);
	void Update(GameCamera *camera, int t);
	virtual void DrawObject(GameCamera *camera);

	int GetFrame();
	virtual Box GetBox(GameCamera *camera);
	int testjump = 20;
	int SimonFall = 0;

	void Hurt(int HTrend);
	void StopHurt(float y);

	void UpStair();
	void SetOnStair(bool);
	bool GetOnStair();
	void OutStair();
	void DownStair();

	void UpdateResetPosition();

	void Resetsimon();
};
#endif
