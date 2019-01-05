#ifndef _AXE_H_
#define _AXE_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define AXE_IMAGE "Resources/weapon/3.png"
#define AXE_VX 8
#define AXE_VY 17
#define AXE_GRAVITY 1
#define AXE_FRAME 50

class Axe : public Weapon
{
public:
	Axe();
	~Axe();

	virtual void Update(GameCamera *camera, int t);
	virtual void Create(float sm_x, float sm_y, int sm_trend);
};
#endif

