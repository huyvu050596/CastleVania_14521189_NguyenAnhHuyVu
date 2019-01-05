#include "Torch.h"


Torch::Torch(float x, float y, int fit)
{
	Type = TORCH;
	Vx = NO_ACTION;
	Vy = NO_ACTION;
	
	Size = new GameTexture(TORCH_IMAGE, 2, 1, 2, ShowBox);
	ObjectSprite = new GameSprite(Size, TORCH_FRAME);

	Trend = RIGHT;
	this->x = x;
	this->y = y;

	if (fit) FitPosision();
}

Torch::~Torch()
{
}

void Torch::Update(GameCamera *camera, int t)
{
	ObjectSprite->Update(t);
}
