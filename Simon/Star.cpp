#include "Star.h"

Star::Star(float x, float y)
{
	this->x = x;
	this->y = y;
	Size = new GameTexture(STAR_IMAGE);
	EffectSprite = new GameSprite(Size, 0);
	WaitingTime = 0;
}

Star::~Star()
{
}

void Star::Draw(GameCamera * camera)
{
	if (WaitingTime % 2 != 0) return;;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	EffectSprite->Draw(pos.x, pos.y);
}

void Star::Update(GameCamera * camera, int t)
{
	WaitingTime += t;
	if (WaitingTime > 300)  FinishEffect = 5;
}
