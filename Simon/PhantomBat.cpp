#include "PhantomBat.h"

PhantomBat::PhantomBat(float x, float y, int fit)
{
	Type = 26;
	Vx = 0;
	Vy = 0;

	Size = new GTexture(PHANTOMBAT_IMAGE_FILE, 3, 1, 3);
	ObjectSprite = new GSprite(Size, PHANTOMBAT_FRAME);

	this->x = x;
	this->y = y;

	Trend = PHANTOMBAT_TREND;

	IsGoing = 0;

	if (fit) FitPosision();
}
PhantomBat::PhantomBat(int iG)
{
	Type = 26;
	this->x = PHANTOMBAT_X;
	this->y = PHANTOMBAT_Y;

	Vx = 0;
	Vy = 0;

	Size = new GTexture(PHANTOMBAT_IMAGE_FILE, 3, 1, 3);
	ObjectSprite = new GSprite(Size, PHANTOMBAT_FRAME);

	IsGoing = 0;
	Trend = PHANTOMBAT_TREND;

	if (iG) this->Go();
}

void PhantomBat::Update(GCamera *camera, int t)
{
	if (IsGoing != 0)
	{
		x += Vx;
		y = sin(x*0.03)*41.3 + 200;
		D3DXVECTOR2 pos = camera->Transform(x, y);

		if (pos.x <= 0)
		{
			this->MoveRigh();
			this->Go();
		}
		if (pos.x >= G_ScreenWidth)
		{
			this->MoveLeft();
			this->Go();
		}

		ObjectSprite->Update(t);
		if (ObjectSprite->_index == 0) ObjectSprite->_index++;
	}
	else ObjectSprite->SelectIndex(PHANTOMBAT_STOP_IMAGE);
}

void PhantomBat::Go()
{
	Object::Go();
	Vx = PHANTOMBAT_VX*Trend;
}