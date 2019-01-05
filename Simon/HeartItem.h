#ifndef _HeartITEM_H_
#define _HeartITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/0.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class HeartItem : public Item
{
	float Dx;
public:
	HeartItem(float x, float y);
	~HeartItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


