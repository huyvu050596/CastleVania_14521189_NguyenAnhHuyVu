#include "CloudIntroGame.h"

CloudIntroGame::CloudIntroGame()
{
	this->x = Game_ScreenWidth;
	this->y = Game_ScreenHeight - 150;

	Trend = 1;
	Vx = -1;
	Vy = 0.03;

	Size = new GameTexture(CLOUD_IMAGE, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, CLOUD_FRAME);
}

void CloudIntroGame::Update(GameCamera *camera, int t)
{
	x += Vx;
	y += Vy;
	ObjectSprite->Update(t);
}