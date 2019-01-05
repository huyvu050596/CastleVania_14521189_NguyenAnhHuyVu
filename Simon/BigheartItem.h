#ifndef _BigheartITEM_H_
#define _BigheartITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/1.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class BigheartItem : public Item
{
public:
	BigheartItem(float x, float y);
	~BigheartItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


