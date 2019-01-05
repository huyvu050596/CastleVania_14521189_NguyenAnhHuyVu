#ifndef _INVISIBLEOBJ_H_
#define _INVISIBLEOBJ_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define IMAGE_FILE "Resources/ground/11.png"

class InvisibleObject :public Object
{
public:
	InvisibleObject(float x, float y, int fit = 1);
	~InvisibleObject();
	void virtual DrawObject(GameCamera *camera);
};
#endif

