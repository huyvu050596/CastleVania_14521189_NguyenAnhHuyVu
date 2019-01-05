#include "Item.h"

Item::Item()
{
	IsFinish = NO_ACTION;
	IsStopFall = NO_ACTION;
	VisibleTime = NO_ACTION;
	WaitingTime = NO_ACTION;
}

Item::~Item()
{
	delete ItemSprite;
	delete Size;
}

void Item::Update(GameCamera *camera, int t)
{
}

void Item::DrawItem(GameCamera *camera)
{
	if (WaitingTime <= WAITINGTIME && TypeItem != POINT_MONEYBAT_ITEM) return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	ItemSprite->Draw(pos.x, pos.y);
}

Box Item::GetBox(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2);
	return Box(pos.x, pos.y, Size->FrameWidth, Size->FrameHeight, Vx, -Vy);
}

int Item::GetFinish()
{
	return IsFinish;
}

void Item::SetFinish()
{
	IsFinish = IS_ACTION;
}

int Item::GetType()
{
	return TypeItem;
}

void Item::StopFall()
{
	IsStopFall = IS_ACTION;
}

int Item::Collide()
{
	if (WaitingTime > WAITINGTIME) return IS_ACTION;
	return NO_ACTION;
}

int Item::GetMoney()
{
	return NO_ACTION;
}
