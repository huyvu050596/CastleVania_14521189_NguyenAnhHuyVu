#include "Candle.h"


Candle::Candle(float x, float y, int fit)
{
	Type = CANDLE;
	Vx = NO_ACTION;
	Vy = NO_ACTION;

	Size = new GameTexture(CANDLE_IMAGE, 2, 1, 2);
	ObjectSprite = new GameSprite(Size, CANDLE_FRAME);

	Trend = RIGHT;
	this->x = x;
	this->y = y;

	if (fit) FitPosision();
}

Candle::~Candle()
{
}

void Candle::Update(GameCamera *camera, int t)
{
	ObjectSprite->Update(t);
}
