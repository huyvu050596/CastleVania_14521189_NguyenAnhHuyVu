#include "Stair2.h"


Stair2::Stair2(float x, float y,int trend, int fit)
{
	Type = STAIR2;
	Vx = NO_ACTION;
	Vy = NO_ACTION;

	if (State == 1 || State == 2) Size = new GameTexture(STAIR2_IMAGE_1, 1, 1, 1, ShowBox);
	ObjectSprite = new GameSprite(Size, 0);

	Trend = RIGHT;
	this->x = x;
	this->y = y;

	if (fit) FitPosision();
}

Stair2::~Stair2()
{
}

void Stair2::Update(GameCamera *camera, int t)
{
	ObjectSprite->Update(t);
}

Box Stair2::GetBox(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2);
	return Box(pos.x, pos.y, Size->FrameWidth - 32, Size->FrameHeight, Vx, -Vy);
}
