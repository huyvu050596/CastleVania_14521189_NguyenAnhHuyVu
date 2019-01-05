#ifndef _WEAPONBOARd_H_
#define _WEAPONBOARd_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

class WeaponBoard :public Object
{
	GameSprite *ObjectSprite[7];

public:
	WeaponBoard();
	~WeaponBoard();
	void DrawObject(int t);
};
#endif

