#ifndef _SWORDITEM_H_
#define _SWORDITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/4.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class SwordItem : public Item
{
public:
	SwordItem(float x, float y);
	~SwordItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


