#ifndef _DOOR_H_
#define _DOOR_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define DOOR_IMAGE_1 "Resources/ground/10.png"
#define DOOR_IMAGE_2 "Resources/ground/10-3.png"
#define DOOR_FRAME 80

class Door :public Object
{
	GameSprite * DoorOpen;
public:
	Door(float, float, int fit = 1);
	~Door();

	virtual void Update(GameCamera *camera, int t);
	void virtual DrawObject(GameCamera *camera);
	virtual Box GetBox(GameCamera * camera, int i);
};
#endif
