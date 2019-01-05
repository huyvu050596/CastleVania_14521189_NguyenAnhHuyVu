#include "Stair.h"


Stair::Stair(float x, float y,int trend, int fit)
{
	Type = STAIR;
	Vx = NO_ACTION;
	Vy = NO_ACTION;

	if(State == 1 || State == 2) Size = new GameTexture(STAIR_IMAGE_1, 1, 1, 1);
	if (State == 3) Size = new GameTexture(STAIR_IMAGE_2, 1, 1, 1);
	ObjectSprite = new GameSprite(Size, 0);

	Trend = trend;
	this->x = x;
	this->y = y;

	if (fit) FitPosision();
}

Stair::~Stair()
{
}

void Stair::Update(GameCamera *camera, int t)
{
	ObjectSprite->Update(t);
}
