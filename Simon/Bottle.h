#ifndef _BOTTLE_H_
#define _BOTTLE_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define BOTTLE_IMAGE "Resources/weapon/2.png"
#define BOTTLE_VX 5
#define BOTTLE_VY 10
#define BOTTLE_GRAVITY 1
#define BOTTLE_FRAME 90

class Bottle : public Weapon
{
	int IsBoom;
	int WaitingTime;
public:
	Bottle();
	~Bottle();

	virtual void Update(GameCamera *camera, int t);
	virtual void Create(float sm_x, float sm_y, int sm_trend);
	virtual void Boom();
	//virtual Box GetBox();
	void DrawWeapon(GameCamera * camera);
};
#endif

