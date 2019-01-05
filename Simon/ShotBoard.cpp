#include "ShotBoard.h"

ShotBoard::ShotBoard()
{
	ObjectSprite[2] = new GameSprite(new GameTexture("Resources/item/11-2.png"), 0);
	ObjectSprite[3] = new GameSprite(new GameTexture("Resources/item/12-2.png"), 0);

	this->x = Game_ScreenWidth / 2 + 230;
	this->y = 60;
}

ShotBoard::~ShotBoard()
{
}

void ShotBoard::DrawObject(int t)
{
	if (t > 1) ObjectSprite[t]->Draw(x, y);
}
