#ifndef _BRICK_H_
#define _BRICK_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define BRICK_IMAGE_1 "Resources/ground/2.png"
#define BRICK_IMAGE_2 "Resources/ground/2-2.png"
#define BRICK_IMAGE_3 "Resources/ground/2-3.png"

class Brick : public Object
{
	float width;
	float height;
public:
	Brick(float x, float y, float w, float h);
	~Brick();
	void virtual DrawObject(GameCamera *camera);

	virtual Box GetBox(GameCamera *camera, int i = 1);
	virtual float GetWidth();
	virtual float GetHeight();
};

#endif

