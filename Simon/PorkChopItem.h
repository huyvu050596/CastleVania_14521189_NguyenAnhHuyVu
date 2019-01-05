#ifndef _PorkChopITEM_H_
#define _PorkChopITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/10.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class PorkChopItem : public Item
{
public:
	PorkChopItem(float x, float y);
	~PorkChopItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


