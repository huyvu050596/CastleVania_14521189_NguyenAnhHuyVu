#include "Potion_Item.h"

Potion_Item::Potion_Item(float x, float y)
{
	TypeItem = POTION_ITEM;
	Size = new GameTexture(ITEM_IMAGE);
	ItemSprite = new GameSprite(Size, 0);
	this->x = x;
	this->y = y;
}

Potion_Item::~Potion_Item()
{
}

void Potion_Item::Update(GameCamera *camera, int t)
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
