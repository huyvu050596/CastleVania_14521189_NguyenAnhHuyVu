#ifndef _BumeranITEM_H_
#define _BumeranITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/8.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class BumeranItem : public Item
{
public:
	BumeranItem(float x, float y);
	~BumeranItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


