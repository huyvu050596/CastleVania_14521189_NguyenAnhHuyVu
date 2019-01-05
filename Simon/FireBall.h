#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define FIREBALL_IMAGE "Resources/fireball.png"
#define FIREBALL_VX 8

class FireBall : public Weapon
{
public:
	FireBall();
	~FireBall();

	virtual void Update(GameCamera *camera, int t);
	virtual void Create(float fm_x, float fm_y, int fm_trend);
};
#endif

