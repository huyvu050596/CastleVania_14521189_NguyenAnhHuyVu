#include "Water.h"

Water::Water(float x, float y)
{
	Size = new GameTexture(WATER_IMAGE);
	EffectSprite = new GameSprite(Size, 0);

	for (int i = 0; i < 3; i++)
	{
		this->x[i] = x;
		this->y[i] = y;
		this->Vx[i] = 0;
	}
	this->Vy[0] = 11;
	this->Vy[1] = 13;
	this->Vy[2] = 12;
}

Water::~Water()
{
}

void Water::Update(GameCamera * camera, int t)
{
	Vy[0]-= 0.9;
	Vy[1] -= 1.1;
	Vy[2] -= 0.8;

	if (Vy[0] > 0) Vx[0] = -5;
	else Vx[0] = 0;
	if (Vy[1] > 0) Vx[1] = 8;
	else Vx[1] = 0;

	x[0] += Vx[0];
	y[0] += Vy[0];
	x[1] += Vx[1];
	y[1] += Vy[1];
	x[2] += Vx[2];
	y[2] += Vy[2];

	if (Vy[0] < -30) FinishEffect = 5;
}

void Water::Draw(GameCamera * camera)
{
	for (int i = 0; i < 3; i++)
	{
		D3DXVECTOR2 pos = camera->Transform(x[i], y[i]);
		EffectSprite->DrawFlipX(pos.x, pos.y);
	}
}
