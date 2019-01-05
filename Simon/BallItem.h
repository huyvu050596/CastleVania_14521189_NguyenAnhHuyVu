#ifndef _BallITEM_H_
#define _BallITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/13.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

#define VISIBLETIME 800

class BallItem : public Item
{
public:
	BallItem(float x, float y);
	~BallItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


