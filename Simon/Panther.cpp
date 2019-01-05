#include "Panther.h"

Panther::Panther(float x, float y, int fit)
{
	Type = 2;
	Vx = 0;
	Vy = 0;

	Size = new GameTexture(PANTHER_IMAGE, 4, 1, 4, ShowBox);
	ObjectSprite = new GameSprite(Size, PANTHER_FRAME);

	this->x = x;
	this->y = y;

	if (fit) FitPosision();
	Trend = PANTHER_TREND;

	IsGoing = 0;

	this->Dx = this->x;
	this->Dy = this->y;
	this->DTrend = this->Trend;
	this->DHealth = this->Health;
}

void Panther::Update(GameCamera *camera, int t)
{
	if (IsJumping == 1)
	{
		Vx *= IsGoing;
		y += Vy;
		x += Vx;
		Vy = Vy - PANTHER_GRAVITY;
		ObjectSprite->SelectIndex(PANTHER_FALL);
		if (Vy <= 0)
		{
			this->Fall();
		}
	}
	else
	if (IsFalling == 1)
	{
		Vx *= IsGoing;
		x += Vx;
		y += Vy;
		Vy = Vy - PANTHER_GRAVITY;
		ObjectSprite->SelectIndex(PANTHER_FALL);
	}
	else
	if (IsGoing == 1)
	{
		x += Vx;
		if (x + Vx + Size->FrameWidth >= camera->_maxSize && !(Dx >= camera->viewport.x && Dx <= camera->viewport.x + Game_ScreenWidth))
		{
			ResetPosition();
		}
		ObjectSprite->Update(t);
		if (ObjectSprite->_index == 0) ObjectSprite->_index++;
	}
	else ObjectSprite->SelectIndex(PANTHER_STOP);
}

void Panther::Go()
{
	Object::Go();
	Vx = PANTHER_VX*Trend;
}

void Panther::Jump()
{
	if (IsJumping == 0 && IsFalling == 0)
	{
		if (IsJumping == 0)
		{
			Vy = PANTHER_FALL + 7;
			Object::Jump();
		}
	}
}

void Panther::Fall()
{
	if (IsJumping == 1 && IsFalling == 0)
	{
		if (IsFalling == 0)
		{
			Vy = -PANTHER_FALL - 7;
			ObjectSprite->SelectIndex(PANTHER_FALL);
			Object::Fall();
		}
	}
}

void Panther::StopFall(float y)
{
	IsFalling = 0;
	this->y = y;
	if (IsGoing == 1) this->Go(); else this->StandUp();
	Vy = 0;
}