#ifndef _STAIR2_H_
#define _STAIR2_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define STAIR2_IMAGE_1 "Resources/ground/4.png"
#define STAIR2_IMAGE_2 "Resources/ground/4-3.png"

class Stair2 : public Object
{
public:
	Stair2(float, float,int trend, int fit = 1);
	~Stair2();

	virtual Box GetBox(GameCamera *camera);
	virtual void Update(GameCamera *camera, int t);
};
#endif
