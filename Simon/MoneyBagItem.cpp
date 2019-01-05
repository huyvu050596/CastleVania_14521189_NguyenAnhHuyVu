#include "MoneyBagItem.h"
#include <string>

MoneyBagItem::MoneyBagItem(float x, float y)
{
	Frame = 0;
	srand(time(NULL));
	int RandomItem = rand() % 10 + 1;
	if (RandomItem < 6) { Index = 0; Money = 100; }
	else
	if (RandomItem < 8) { Index = 2; Money = 400; }
	else 
	if (RandomItem < 10) { Index = 1; Money = 700; }
	else
	{
		Frame = 15; 
		Money = 2000;
	}
	TypeItem = 2;
	Size = new GameTexture(ITEM_IMAGE, 3, 1, 3);
	ItemSprite = new GameSprite(Size, Frame);
	this->x = x;
	this->y = y;
}

MoneyBagItem::MoneyBagItem(int Value, float x, float y)
{
	Frame = 0;
	Index = 0;
	TypeItem = 20;
	if (Value == 100) Size = new GameTexture("Resources/item/100.png");
	if (Value == 400) Size = new GameTexture("Resources/item/400.png");
	if (Value == 700) Size = new GameTexture("Resources/item/700.png");
	if (Value == 2000) Size = new GameTexture("Resources/item/2000.png");

	ItemSprite = new GameSprite(Size, Frame);
	this->x = x + 20;
	this->y = y;
}

MoneyBagItem::~MoneyBagItem()
{
}

void MoneyBagItem::DrawItem(GameCamera * camera)
{
	if (Frame == 0) ItemSprite->SelectIndex(Index);
	Item::DrawItem(camera);
}

void MoneyBagItem::Update(GameCamera *camera, int t)
{
	if (TypeItem == 20)
	{
		VisibleTime += 1;
		if (VisibleTime > 25) IsFinish = 1;
		return;
	}

	if (WaitingTime <= WAITINGTIME)
	{
		WaitingTime += t;
		return;
	}

	if (IsStopFall == 1)
	{
		Vy = 0;
		Vx = 0;
		VisibleTime += t;
		if (VisibleTime > VISIBLETIME) IsFinish = 1;
	}
	y += Vy;
	Vy -= ITEM_GRAVITY;
}

int MoneyBagItem::GetMoney()
{
	return Money;
}
