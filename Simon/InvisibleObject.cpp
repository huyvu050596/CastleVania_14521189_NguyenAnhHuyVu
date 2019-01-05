
#include "InvisibleObject.h"


InvisibleObject::InvisibleObject(float x, float y,int fit)
{
	this->x = x;
	this->y = y;
	
	Size = new GameTexture(IMAGE_FILE, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = RIGHT;
	Type = INVISIBLE_OBJECT;

	if (fit) FitPosision();
}

InvisibleObject::~InvisibleObject()
{
}

void InvisibleObject::DrawObject(GameCamera *camera)
{
	if (!DrawInvisibleObj) return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == LEFT) ObjectSprite->Draw(pos.x, pos.y);
	else ObjectSprite->DrawFlipX(pos.x, pos.y);
}
