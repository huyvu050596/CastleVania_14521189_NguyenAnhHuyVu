#ifndef _BOSSBAT_H_
#define _BOSSBAT_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define BOSSBAT_IMAGE "Resources/boss/0.png"
#define BOSSBAT_FRAME_NRM 70
#define BOSSBAT_FRAME_ATK 30
#define BOSSBAT_STOP 0

#define BOSSBAT_VX 4.0f

#define BOSSBAT_GRAVITY 10
#define BOSSBAT_FALL 180
#define BOSSBAT_VX_DAMAGED 150
#define BOSSBAT_VY_DAMAGED 450

class BossBat : public Object
{
	int WaitingTime;
	int WT;
	int Status;
	float sm_x, sm_y;
	float y_before;
	int sm_Trend;
	float x1, y1;
	float x2, y2;
	float a, b;

public:
	BossBat(float x, float y, int fit = 1);
	~BossBat();

	virtual void Go();
	virtual void Update(GameCamera *camera,int t);

	virtual void GetSMPositionForBoss(float x, float y, int Trend);

	float FindX(GameCamera *camera);
	float FindY(GameCamera *camera);

	virtual void ResetPosition();
};
#endif
