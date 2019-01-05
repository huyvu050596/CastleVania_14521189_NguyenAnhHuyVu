#include "Bat.h"

Bat::Bat(float x, float y, int fit)
{
	Type = 0;
	Vx = 0;
	Vy = 0;

	Size = new GameTexture(BAT_IMAGE, 4, 1, 4);
	ObjectSprite = new GameSprite(Size, BAT_FRAME);

	this->x = x;
	this->y = y;
	this->BatY = y;

	Trend = BAT_TREND;

	IsGoing = 0;

	if (fit) FitPosision();

	this->Dx = this->x;
	this->Dy = this->y;
	this->DTrend = this->Trend;
	this->DHealth = this->Health;
}

void Bat::Update(GameCamera *camera,int t)
{
	if (IsGoing != 0)
	{
		x += Vx;
		y = sin(x*0.03)*41.3 + BatY;
		ObjectSprite->Update(t);
		if (ObjectSprite->_index == 0) ObjectSprite->_index++;
	}
	else ObjectSprite->SelectIndex(BAT_STOP);
}

void Bat::Go()
{
	Object::Go();
	Vx = BAT_VX*Trend;
}