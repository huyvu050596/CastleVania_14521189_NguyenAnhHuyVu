
#ifndef _FISHMAN_H_
#define _FISHMAN_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define FISHMAN_IMAGE "Resources/enemy/3.png"
#define FISHMAN_TREND 1
#define FISHMAN_FRAME 100
#define FISHMAN_STOP 2
#define FISHMAN_X 300
#define FISHMAN_Y 70

#define FISHMAN_VX 3.0f
#define FISHMAN_JUMP 28
#define FISHMAN_GRAVITY 1
#define FISHMAN_FALL 180
#define FISHMAN_VX_DAMAGED 150
#define FISHMAN_VY_DAMAGED 450

#include "FireBall.h"

class FishMan : public Object
{
	int FMJump = 0;
	int FMAtk = 0;
	int IsCreateBullet;
	int WaitingAtk;

public:
	FishMan(float x, float y, int fit = 1);
	~FishMan();

	virtual void Attack(Weapon *w = NULL);
	virtual void Jump();
	virtual void Fall();
	void StopFall(float y);
	virtual void Go();
	virtual void Update(GameCamera *camera, int t);

	virtual int CreateWeapon();
	virtual void SetCreateWeapon();
	
	virtual void ResetPosition();
};
#endif
