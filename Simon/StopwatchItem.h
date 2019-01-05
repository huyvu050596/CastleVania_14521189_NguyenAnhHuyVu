#ifndef _StopwatchITEM_H_
#define _StopwatchITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Item.h"
#include "Global.h"

#define ITEM_IMAGE "Resources/item/5.png"
#define ITEM_VY -7
#define ITEM_GRAVITY 1
#define ITEM_FRAME 15

class StopwatchItem : public Item
{
public:
	StopwatchItem(float x, float y);
	~StopwatchItem();

	virtual void Update(GameCamera *camera, int t);
};
#endif


