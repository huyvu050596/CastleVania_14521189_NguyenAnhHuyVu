#ifndef _STAR_H_
#define _STAR_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Effect.h"

#define STAR_IMAGE "Resources/other/0.png"

class Star : public Effect
{
	int IsDraw;
	int WaitingTime;
public:
	Star(float x, float y);
	virtual void Draw(GameCamera *camera);
	virtual void Update(GameCamera *camera, int t);
	~Star();
};
#endif

