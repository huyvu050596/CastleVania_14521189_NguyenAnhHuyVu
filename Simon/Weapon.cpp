#include "Weapon.h"

Weapon::Weapon()
{
	IsFinish = IS_ACTION;
}

Weapon::~Weapon()
{
	delete WeaponSprite;
	delete Size;
}

void Weapon::Update(GameCamera *camera, int t)
{

}

void Weapon::Create(float sm_x, float sm_y, int sm_trend)
{
	this->x = sm_x;
	this->y = sm_y;
	Trend = sm_trend;
	IsFinish = NO_ACTION;
	WeaponSprite->Reset();
}

void Weapon::DrawWeapon(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == DefaultTrend) WeaponSprite->Draw(pos.x, pos.y);
	else WeaponSprite->DrawFlipX(pos.x, pos.y);
}

int Weapon::GetTrend()
{
	return Trend;
}

void Weapon::SetTrend(int a)
{
	Trend = a;
}

Box Weapon::GetBox(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2);
	return Box(pos.x, pos.y, Size->FrameWidth, Size->FrameHeight, Vx, -Vy);
}

void Weapon::SetXY(float x, float y)
{
	simon_x = x;
	simon_y = y;
}

void Weapon::SetTypeMorningStar(int i)
{
}

int Weapon::GetTypeMorningStar()
{
	return NO_ACTION;
}

int Weapon::GetFinish()
{
	return IsFinish;
}

void Weapon::SetFinish()
{
	IsFinish = IS_ACTION;
}

int Weapon::GetType()
{
	return WeaponType;
}

void Weapon::Boom()
{
}

void Weapon::BumeranBack()
{
}

