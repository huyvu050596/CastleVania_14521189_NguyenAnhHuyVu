#include "HeartItem.h"

HeartItem::HeartItem(float x, float y)
{
	TypeItem = HEART_ITEM;
	Size = new GameTexture(ITEM_IMAGE);
	ItemSprite = new GameSprite(Size, 0);
	this->Dx = x;
	this->y = y;
	Vy = -0.75;
}

HeartItem::~HeartItem()
{
}

void HeartItem::Update(GameCamera *camera, int t)
{
	if (WaitingTime <= WAITINGTIME)
	{
		WaitingTime += t;
		return;
	}

	if (IsStopFall == IS_ACTION)
	{
		Vy = NO_ACTION;
		Vx = NO_ACTION;
		VisibleTime += t;
		if (VisibleTime > VISIBLETIME) IsFinish = IS_ACTION;
	}

	y += Vy;
	x = sin(y*0.09)*43.3 + Dx;
}
