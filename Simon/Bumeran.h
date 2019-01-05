#ifndef _BUMERAN_H_
#define _BUMERAN_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define BUMERAN_IMAGE "Resources/weapon/4.png"
#define BUMERAN_FRAME 7
#define BUMERAN_VX 20

class Bumeran : public Weapon
{
public:
	Bumeran();
	~Bumeran();

	virtual void Update(GameCamera *camera, int t);
	virtual void Create(float sm_x, float sm_y, int sm_trend);

	virtual void BumeranBack();
};
#endif

