#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	this->x = 0;
	this->y = 0;

	Size = new GameTexture(IMAGE_FILE, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = 1;
	Type = 30;

	FitPosision();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::DrawObject(GameCamera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	ObjectSprite->Draw(pos.x, pos.y);
}
