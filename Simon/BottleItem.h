#ifndef _BOTTLEITEM_H_
#define _BOTTLEITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/9.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class BottleItem : public Item
{
public:
	BottleItem(float x, float y);
	~BottleItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


