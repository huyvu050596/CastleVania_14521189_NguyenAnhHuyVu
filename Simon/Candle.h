#ifndef _CANDLE_H_
#define _CANDLE_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define CANDLE_IMAGE "Resources/ground/1.png"
#define CANDLE_FRAME 100

class Candle :public Object
{
public:
	Candle(float, float, int fit = 1);
	~Candle();

	virtual void Update(GameCamera *camera, int t);
};
#endif
