
#ifndef _PANTHER_H_
#define _PANTHER_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define PANTHER_IMAGE "Resources/enemy/2.png"
#define PANTHER_TREND -1
#define PANTHER_FRAME 40
#define PANTHER_STOP 0
#define PANTHER_FALL 3

#define PANTHER_VX 7

#define PANTHER_GRAVITY 2
//#define PANTHER_FALL 10

class Panther : public Object
{
public:
	Panther(int iG = 0);
	Panther(float x, float y, int fit = 1);
	~Panther();

	virtual void Fall();
	virtual void Go();
	virtual void Jump();
	virtual void Update(GameCamera *camera, int t);
	void StopFall(float y);
};
#endif
