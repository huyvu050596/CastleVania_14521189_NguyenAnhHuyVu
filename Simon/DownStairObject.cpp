
#include "DownStairObject.h"


DownStairObject::DownStairObject(float x, float y,int trend, int fit)
{
	this->x = x;
	this->y = y;

	Size = new GameTexture(IMAGE_FILE, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = trend;
	Type = DOWN_STAIR_OBJECT;

	if (fit) FitPosision();
}

DownStairObject::~DownStairObject()
{
}


void DownStairObject::DrawObject(GameCamera *camera)
{
	if (!DrawInvisibleObj) return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == LEFT) ObjectSprite->Draw(pos.x, pos.y);
	else ObjectSprite->DrawFlipX(pos.x, pos.y);
}


