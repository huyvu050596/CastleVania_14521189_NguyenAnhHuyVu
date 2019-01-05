#include "FishMan.h"

FishMan::FishMan(float x, float y, int fit)
{
	Type = 3;
	Vx = 0;
	Vy = 0;

	Size = new GameTexture(FISHMAN_IMAGE, 3, 1, 3, ShowBox);
	ObjectSprite = new GameSprite(Size, FISHMAN_FRAME);

	this->x = x;
	this->y = y;

	Trend = -1;

 	IsGoing = 0;
	FMJump = 0;
	if (fit) FitPosision();
	IsCreateBullet = 0;

	srand(time(NULL));
	WaitingAtk = rand() % (200 - 100 + 1) + 100;

	this->Dx = this->x;
	this->Dy = this->y;
	this->DTrend = this->Trend;
	this->DHealth = this->Health;
}

void FishMan::Update(GameCamera *camera, int t)
{
	if (Water > 0) Water--;
	if (IsAttacking == 1 || FMAtk > 0)      
	{
		ObjectSprite->Update(t);
		if (ObjectSprite->_index > 0)
		{
			FMAtk++;
			ObjectSprite->SelectIndex(FISHMAN_STOP);
			if (FMAtk == 6)
			{
				FMAtk = 0;
				IsAttacking = 0;
				this->Go();
				return;
			}
			if (FMAtk == 3 && IsCreateBullet == 0)
			{
				IsCreateBullet = 1;
			}
		}
	}
	else
	{
		if (IsJumping == 1)
		{
			Vx *= IsGoing;
			y += Vy;
			x += Vx;
			Vy = Vy - FISHMAN_GRAVITY;
			ObjectSprite->SelectIndex(FISHMAN_STOP);
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
			Vy = Vy - FISHMAN_GRAVITY;
			ObjectSprite->SelectIndex(FISHMAN_STOP);
		}
		else
		if (IsGoing == 1)
		{
			x += Vx;

			if (x <= camera->_minSize)
			{
				this->MoveRight();
				this->Go();
			}
			
			FMAtk--;
			if (FMAtk <= -WaitingAtk)
			{
				FMAtk = 0;
				srand(time(NULL));
				WaitingAtk = rand() % (200 - 150 + 1) + 150;
				this->Attack();
			}
			ObjectSprite->Update(t);
			if (ObjectSprite->_index == 0) ObjectSprite->_index++;
		}
		else ObjectSprite->SelectIndex(FISHMAN_STOP);
	}
}

void FishMan::Go()
{
	if (FMJump == 0)
	{
		FMJump = 1;
		Jump();
		return;
	}
	if (IsJumping == 1 || IsFalling == 1) return;
	if (IsAttacking == 0)
	{
		this->Vx = FISHMAN_VX*Trend;
		Object::Go();
	}
}

void FishMan::Jump()
{
	if (IsAttacking == 0 && IsJumping == 0 && IsFalling == 0)
	{
		if (IsJumping == 0)
		{
			Vy = FISHMAN_JUMP;
			ObjectSprite->SelectIndex(FISHMAN_STOP);
			Object::Jump();
		}
	}
}

void FishMan::Fall()
{
	if (IsAttacking == 0 && IsJumping == 1 && IsFalling == 0)
	{
		if (IsFalling == 0)
		{
			Vy = -FISHMAN_JUMP;
			ObjectSprite->SelectIndex(FISHMAN_STOP);
			Object::Fall();
		}
	}
}

void FishMan::StopFall(float y)
{
	IsFalling = 0;
	this->y = y;
	this->Go();
	Vy = 0;
}

void FishMan::Attack(Weapon *w)
{
	if (IsAttacking == 1) return;
	if (IsFalling == 1) return;
	FMAtk = 1;
	IsCreateBullet = 0;
	ObjectSprite->SelectIndex(0);
	if (w) Object::Attack(w);
}

int FishMan::CreateWeapon()
{
	return IsCreateBullet;
}

void FishMan::SetCreateWeapon()
{
	IsCreateBullet = 0;
}

void FishMan::ResetPosition()
{
	FMJump = 0;
	IsCreateBullet = 0;

	srand(time(NULL));
	WaitingAtk = rand() % (200 - 100 + 1) + 100;

	Object::ResetPosition();
}