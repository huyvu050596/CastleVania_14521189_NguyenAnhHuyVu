#include "BatIntroGame.h"

BatIntroGame::BatIntroGame()
{
	this->x = BAT_X;
	this->y = BAT_Y;

	Trend = 1;
	Vx = 1.2;
	Vy = 0.25;

	Size = new GameTexture(BAT_IMAGE, 2, 1, 2);
	ObjectSprite = new GameSprite(Size, BAT_FRAME);
}

void BatIntroGame::Update(GameCamera *camera, int t)
{
	x += Vx;
	y += Vy;
	ObjectSprite->Update(t);
}