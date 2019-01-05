#ifndef _DOWNSTAIROBJ_H_
#define _DOWNSTAIROBJ_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define IMAGE_FILE "Resources/ground/6.png"

class DownStairObject :public Object
{
public:
	DownStairObject(float x, float y,int trend, int fit = 1);
	~DownStairObject();
	void virtual DrawObject(GameCamera *camera);
};
#endif
