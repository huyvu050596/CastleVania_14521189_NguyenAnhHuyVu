#ifndef _II_ITEM_H_
#define _II_ITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/11.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class II_Item : public Item
{
public:
	II_Item(float x, float y);
	~II_Item();

	virtual void Update(GameCamera *camera, int t);
};
#endif


