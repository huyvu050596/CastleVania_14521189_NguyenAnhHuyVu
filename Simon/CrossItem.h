#ifndef _CrossITEM_H_
#define _CrossITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/6.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class CrossItem : public Item
{
public:
	CrossItem(float x, float y);
	~CrossItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


