#include "III_Item.h"

III_Item::III_Item(float x, float y)
{
	TypeItem = SHOT3_ITEM;
	Size = new GameTexture(ITEM_IMAGE);
	ItemSprite = new GameSprite(Size, 0);
	this->x = x;
	this->y = y;
}

III_Item::~III_Item()
{
}

void III_Item::Update(GameCamera *camera, int t)
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
