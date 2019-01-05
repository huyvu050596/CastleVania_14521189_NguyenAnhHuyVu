
#include "UpStairObject.h"

UpStairObject::UpStairObject(float x, float y,int trend, int fit)
{
	this->x = x;
	this->y = y;

	Size = new GameTexture(IMAGE_FILE, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = trend;
	Type = UP_STAIR_OBJECT;

	if (fit) FitPosision();
}

UpStairObject::~UpStairObject()
{
}

void UpStairObject::DrawObject(GameCamera *camera)
{
	if (!DrawInvisibleObj) return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == -1) ObjectSprite->Draw(pos.x, pos.y);
	else ObjectSprite->DrawFlipX(pos.x, pos.y);
}
