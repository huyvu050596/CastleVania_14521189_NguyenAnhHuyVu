
#ifndef _GHOUL_H_
#define _GHOUL_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define GHOUL_IMAGE "Resources/enemy/1.png"
#define GHOUL_TREND -1
#define GHOUL_FRAME 100
#define GHOUL_STOP 0

#define GHOUL_VX 4

#define GHOUL_FALL_IMAGE 0
#define GHOUL_GRAVITY 2
#define GHOUL_FALL 10

class Ghoul : public Object
{
	int GoBack;
public:
	Ghoul(int iG);
	Ghoul(float x, float y, int fit = 1);
	~Ghoul();

	virtual void Go();
	virtual void Jump();
	virtual void Fall();
	virtual void StopFall(float y);
	virtual void Update(GameCamera *camera, int t);
	virtual Box GetBox(GameCamera * camera, int i = 1);
};
#endif
