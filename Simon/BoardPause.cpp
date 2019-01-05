#include "BoardPause.h"

BoardPause::BoardPause()
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

BoardPause::~BoardPause()
{
}

void BoardPause::DrawObject(GameCamera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	ObjectSprite->Draw(pos.x, pos.y);
}
