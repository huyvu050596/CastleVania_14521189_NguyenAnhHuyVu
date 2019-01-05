#ifndef _FIRE_H_
#define _FIRE_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Effect.h"

#define FIRE_IMAGE "Resources/other/1.png"
#define FIRE_FRAME 100

class Fire : public Effect
{
public:
	Fire(float x, float y);
	virtual void Update(GameCamera *camera, int t);
	~Fire();
};
#endif

