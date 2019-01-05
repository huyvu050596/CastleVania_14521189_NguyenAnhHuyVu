#include "WeaponBoard.h"

WeaponBoard::WeaponBoard()
{
	ObjectSprite[0] = new GameSprite(new GameTexture("Resources/item/3.png"), 0);
	ObjectSprite[1] = new GameSprite(new GameTexture("Resources/item/4.png"), 0);
	ObjectSprite[2] = new GameSprite(new GameTexture("Resources/item/9.png"), 0);
	ObjectSprite[3] = new GameSprite(new GameTexture("Resources/item/7.png"), 0);
	ObjectSprite[4] = new GameSprite(new GameTexture("Resources/item/8.png"), 0);
	ObjectSprite[5] = new GameSprite(new GameTexture("Resources/item/5.png"), 0);
	ObjectSprite[6] = new GameSprite(new GameTexture("Resources/item/6.png"), 0);

	this->x = Game_ScreenWidth / 2 + 105;
	this->y = 55;
}

WeaponBoard::~WeaponBoard()
{
}

void WeaponBoard::DrawObject(int t)
{
	if (t>= 0) ObjectSprite[t]->Draw(x, y);
}
