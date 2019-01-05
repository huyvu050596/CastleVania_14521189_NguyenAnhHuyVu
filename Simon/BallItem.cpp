#include "BallItem.h"

BallItem::BallItem(float x, float y)
{
	TypeItem = BALL_ITEM;
	Size = new GameTexture(ITEM_IMAGE, 2, 1, 2);
	ItemSprite = new GameSprite(Size, 10);
	this->x = x;
	this->y = y;
}

BallItem::~BallItem()
{
}

void BallItem::Update(GameCamera *camera, int t)
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
	}
	y += Vy;
	Vy -= ITEM_GRAVITY;
}
