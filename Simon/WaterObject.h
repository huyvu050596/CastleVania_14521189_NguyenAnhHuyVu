#ifndef _WATEROBJ_H_
#define _WATEROBJ_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define IMAGE_FILE "Resources/ground/13.png"

class WaterObject :public Object
{
public:
	WaterObject(float x, float y, int fit = 1);
	~WaterObject();
	void virtual DrawObject(GameCamera *camera);
};
#endif

