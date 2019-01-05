#ifndef _WATER_H_
#define _WATER_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Effect.h"

#define WATER_IMAGE "Resources/other/2.png"
#define WATER_FRAME 100

class Water : public Effect
{
	float x[3];
	float y[3];
	float Vx[3];
	float Vy[3];

public:
	Water(float x, float y);
	virtual void Update(GameCamera *camera, int t);
	virtual void Draw(GameCamera *camera);
	~Water();
};
#endif

