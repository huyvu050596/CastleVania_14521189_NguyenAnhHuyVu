#include "BottleItem.h"

BottleItem::BottleItem(float x, float y)
{
	TypeItem = BOTTLE_ITEM;
	Size = new GameTexture(ITEM_IMAGE);
	ItemSprite = new GameSprite(Size, 0);
	this->x = x;
	this->y = y;
}

BottleItem::~BottleItem()
{
}

void BottleItem::Update(GameCamera *camera, int t)
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
	Vy -= ITEM_GRAVITY;
}
