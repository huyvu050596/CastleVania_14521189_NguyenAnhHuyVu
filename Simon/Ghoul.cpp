#include "Ghoul.h"
#include <cstdlib>
#include <ctime>

Ghoul::Ghoul(float x, float y, int fit)
{
	Type = 1;
	Vx = 0;
	Vy = 0;

	Size = new GameTexture(GHOUL_IMAGE, 2, 1, 2, ShowBox);
	ObjectSprite = new GameSprite(Size, GHOUL_FRAME);

	this->x = x;
	this->y = y;

	Trend = GHOUL_TREND;

	IsGoing = 0;

	if (fit) FitPosision();

	this->Dx = this->x;
	this->Dy = this->y;
	this->DTrend = this->Trend;
	this->DHealth = this->Health;
}

void Ghoul::Update(GameCamera *camera, int t)
{
	if (IsJumping == 1)
	{
		Vx *= IsGoing;
		y += Vy;
		x += Vx;
		Vy = Vy - GHOUL_GRAVITY;
		ObjectSprite->SelectIndex(GHOUL_FALL_IMAGE);
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
		Vy = Vy - GHOUL_GRAVITY;
		ObjectSprite->SelectIndex(GHOUL_FALL_IMAGE);
	}
	else
	if (IsGoing == 1)
	{
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x < - Size->FrameWidth)
		{
			GoBack = 1;
		}
		if (pos.x > Game_ScreenWidth + Size->FrameWidth / 2 && GoBack)
		{
			this->Health = 0;
			return;
		}
		if (GoBack && pos.x > -Game_ScreenWidth && pos.x < -Game_ScreenWidth / 2)
		{
			MoveRight();
			Go();
			return;
		}
		ObjectSprite->Update(t);
	}
	else ObjectSprite->SelectIndex(GHOUL_STOP);
}

void Ghoul::Go()
{
	Object::Go();
	Vx = GHOUL_VX*Trend;
}


void Ghoul::Jump()
{
	if (IsJumping == 0 && IsFalling == 0)
	{
		if (IsJumping == 0)
		{
			Vy = GHOUL_FALL;
			Object::Jump();
		}
	}
}


void Ghoul::Fall()
{
	if (IsJumping == 1 && IsFalling == 0)
	{
		if (IsFalling == 0)
		{
			Vy = -GHOUL_FALL;
			ObjectSprite->SelectIndex(GHOUL_FALL_IMAGE);
			Object::Fall();
		}
	}
}

void Ghoul::StopFall(float y)
{
	IsFalling = 0;
	this->y = y;
	if (IsGoing == 1) this->Go(); else this->StandUp();
	Vy = 0;
}

Box Ghoul::GetBox(GameCamera *camera, int i)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2 - 10);
	return Box(pos.x, pos.y, Size->FrameWidth, Size->FrameHeight - 10, Vx, -Vy);
}