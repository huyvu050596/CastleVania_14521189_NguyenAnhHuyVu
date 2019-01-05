#include "Fire.h"

Fire::Fire(float x, float y)
{
	Size = new GameTexture(FIRE_IMAGE, 3, 1, 3);
	EffectSprite = new GameSprite(Size, 50);
	this->x = x;
	this->y = y;
}

Fire::~Fire()
{
}

void Fire::Update(GameCamera * camera, int t)
{
	Effect::Update(camera, t);
	if (EffectSprite->_index == 2)  FinishEffect ++;
}
