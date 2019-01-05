
#ifndef _PHANTOMBAT_H_
#define _PHANTOMBAT_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define PHANTOMBAT_IMAGE_FILE "Resources/boss/0.png"
#define PHANTOMBAT_TREND 1
#define PHANTOMBAT_FRAME 100
#define PHANTOMBAT_STOP_IMAGE 0
#define PHANTOMBAT_X 50
#define PHANTOMBAT_Y 160

#define PHANTOMBAT_VX 4.0f

#define PHANTOMBAT_GRAVITY 20
#define PHANTOMBAT_FALL 180
#define PHANTOMBAT_VX_DAMAGED 150
#define PHANTOMBAT_VY_DAMAGED 450

class PhantomBat : public Object
{
public:
	PhantomBat(int iG = 0);
	PhantomBat(float x, float y, int fit = 1);
	~PhantomBat();

	virtual void Go();
	virtual void Update(GameCamera *camera, int t);
};
#endif
