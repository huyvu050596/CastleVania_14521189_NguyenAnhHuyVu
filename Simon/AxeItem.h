#ifndef _AXEITEM_H_
#define _AXEITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/7.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class AxeItem : public Item
{
public:
	AxeItem(float x, float y);
	~AxeItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


