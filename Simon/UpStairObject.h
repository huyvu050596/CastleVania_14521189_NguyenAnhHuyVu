#ifndef _UPSTARIOBJ_H_
#define _UPSTAIROBJ_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define IMAGE_FILE "Resources/ground/5.png"

class UpStairObject :public Object
{
public:
	UpStairObject(float x, float y,int trend, int fit = 1);
	~UpStairObject();
	void virtual DrawObject(GameCamera *camera);
};
#endif

