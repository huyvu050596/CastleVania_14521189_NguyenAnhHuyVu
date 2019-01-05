#ifndef _STAIR_H_
#define _STAIR_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define STAIR_IMAGE_1 "Resources/ground/3.png"
#define STAIR_IMAGE_2 "Resources/ground/3-3.png"

class Stair : public Object
{
public:
	Stair(float, float,int trend, int fit = 1);
	~Stair();

	virtual void Update(GameCamera *camera, int t);
};
#endif
