#ifndef _MORNINGSTAR_H_
#define _MORNINGSTAR_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Weapon.h"
#include "Global.h"

#define MORNINGSTAR_IMAGE "Resources/weapon/morningstar.png"
#define MORNINGSTAR_FRAME 70

class MorningStar : public Weapon
{
	int TypeMorningStar;

public:
	MorningStar();
	~MorningStar();

	virtual void Update(GameCamera *camera, int t);
	virtual Box GetBox(GameCamera *camera);
	virtual void DrawWeapon(GameCamera *camera);
	virtual void SetXY(float x, float y);

	virtual void SetTypeMorningStar(int i = -1);
	virtual int GetTypeMorningStar(); 
	virtual void Create(float sm_x, float sm_y, int sm_trend);
};
#endif

