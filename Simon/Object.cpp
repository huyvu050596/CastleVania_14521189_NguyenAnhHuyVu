#include "Object.h"

Object::Object()
{
	id = NO_ACTION;
	Health = IS_ACTION;
	Water = NO_ACTION;
}

Object::~Object() 
{
	if (ObjectSprite) delete ObjectSprite;
	if (Size) delete Size;
}

int Object::GetID() { return id; }
float Object::GetX() {return x;}
float Object::GetY() {return y;}
float Object::GetWidth(){ return Size->FrameWidth; }
float Object::GetHeight(){ return Size->FrameHeight; }
void Object::SetX(float a) { x = a; }
void Object::SetY(float b) { y = b; }

float Object::GetVx() 
{
	if (IsAttacking == IS_ACTION) return NO_ACTION;
	if (IsGoing == IS_ACTION) return Vx;
	return NO_ACTION;
}

float Object::GetVy() 
{
	if (IsAttacking == IS_ACTION) return NO_ACTION;
	if (IsFalling == IS_ACTION || IsJumping == IS_ACTION) return Vy;
	return NO_ACTION;
}

int Object::GetMoving() {return IsGoing;}
void Object::SetMoving(int a) {IsGoing = a;}

int Object::GetTrend() { return Trend; }
void Object::SetTrend(int a) { Trend = a; }

int Object::GetFalling()
{
	return IsFalling;
}

int Object::GetJumping()
{
	return IsJumping;
}

int Object::GetType() { return Type;}

int Object::GetAlive()
{
	return Health;
}

void Object::SetAlive(int t)
{
	Health = Health - t;
	if (Health < 0) Health = 0;
	if (Health > 20) Health = 20;
	if (t > 0 && Health > 0) IsHurting = 25 + 25 * (Type == SIMON_OBJECT);
}

void Object::Update(GameCamera *camera, int t){}

void Object::DrawObject(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (IsHurting)
	{
		IsHurting--;
		if (Type == SIMON_OBJECT)    
		{
			if (!IsDraw)
			{
				IsDraw = true;
				return;
			}
			else
			{
				IsDraw = false;
			}
		}
	}
	else EndHurt = IS_ACTION;
	
	if (Trend == LEFT) ObjectSprite->Draw(pos.x, pos.y);
	else ObjectSprite->DrawFlipX(pos.x, pos.y);
}

int Object::GetAttacking() 
{
	return IsAttacking;
}

void Object::MoveLeft()
{
	if (IsFalling || IsJumping) return;
	if (IsAttacking == IS_ACTION) return;
	Trend = LEFT;
}

void Object::MoveRight()
{
	if (IsFalling || IsJumping) return;
	if (IsAttacking == IS_ACTION) return;
	Trend = RIGHT;
}

void Object::Stop()
{
	IsGoing = NO_ACTION;
	Vx = NO_ACTION;
}

void Object::Sit()
{
	IsSitting = IS_ACTION;
	IsFalling = NO_ACTION;
	IsJumping = NO_ACTION;
	IsGoing = NO_ACTION;
}

void Object::StandUp()
{
	IsSitting = NO_ACTION;
	IsFalling = NO_ACTION;
	IsJumping = NO_ACTION;
	IsGoing = NO_ACTION;
}

void Object::Fall()
{
	IsFalling = IS_ACTION;
	IsJumping = NO_ACTION;
	IsSitting = NO_ACTION;
	EndHurt = IS_ACTION;
}

void Object::StopFall(float y)
{
}

void Object::Jump()
{
	IsJumping = IS_ACTION;
	IsFalling = NO_ACTION;
	IsSitting = NO_ACTION;
}

void Object::Attack(Weapon *weapon)
{
	IsAttacking = IS_ACTION;
	if (weapon) weapon->Create(x, y, Trend);
}

void Object::Go()
{
	IsSitting = NO_ACTION;
	IsFalling = NO_ACTION;
	IsJumping = NO_ACTION;
	IsGoing = IS_ACTION;
}

void Object::SetId(int a)
{
	id = a;
}

Box Object::GetBox(GameCamera *camera,int i)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2);
	return Box(pos.x, pos.y, Size->FrameWidth, Size->FrameHeight, Vx, -Vy);
}

void Object::ResetObj()
{
	Trend = DTrend;
	x = Dx;
	y = Dy;
}

void Object::FitPosision()
{
	if (ReadFileNew) return;
	this->x = x + Size->FrameWidth / 2;
	this->y = y - Size->FrameHeight / 2;
}

void Object::Hurting()
{
	IsDraw = true;
	IsHurting = IS_ACTION;
}

void Object::SetAnimation(float Vx, float Vy, int Frame)
{
	this->Vx = Vx*Trend;
	this->Vy = Vy;
	this->ObjectSprite->_timeAni = Frame;
}


int Object::GetHurt()
{
	if (IsHurting) return IS_ACTION;
	return NO_ACTION;
}

void Object::SetHurt(int i)
{
	IsHurting = i;
}

int Object::CreateWeapon()
{
	return NO_ACTION;
}

void Object::SetCreateWeapon()
{
}

void Object::GetSMPositionForBoss(float x, float y, int Trend)
{
}

void Object::ResetPosition()
{
	x = Dx;
	y = Dy;
	Trend = DTrend;
	Stop();
}

void Object::BackupPosition()
{
	Dx = x;
	Dy = y;
	DTrend = Trend;
}


 
