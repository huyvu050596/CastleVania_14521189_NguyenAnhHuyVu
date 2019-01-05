#ifndef _SWORD_H_
#define _SWORD_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define SWORD_IMAGE "Resources/weapon/1.png"
#define SWORD_VX 8

class Sword : public Weapon
{
public:
	Sword();
	~Sword();

	virtual void Update(GameCamera *camera, int t);
	virtual void Create(float sm_x, float sm_y, int sm_trend);
};
#endif

