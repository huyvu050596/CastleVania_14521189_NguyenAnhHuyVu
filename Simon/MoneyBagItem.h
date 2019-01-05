#ifndef _MoneyBagITEM_H_
#define _MoneyBagITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"

#define ITEM_IMAGE "Resources/item/2.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class MoneyBagItem : public Item
{
	int Money;
	int Frame;
	int Index;
public:
	MoneyBagItem(float x, float y);
	MoneyBagItem(int Value, float x, float y);
	~MoneyBagItem();

	virtual void DrawItem(GameCamera *camera);
	virtual void Update(GameCamera *camera, int t);
	virtual int GetMoney();
};
#endif


