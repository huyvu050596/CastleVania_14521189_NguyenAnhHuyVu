#include "MorningStar.h"

MorningStar::MorningStar()
{
	WeaponType = MORNING_STAR;
	Size = new GameTexture(MORNINGSTAR_IMAGE, 4, 3, 12);
	WeaponSprite = new GameSprite(Size, MORNINGSTAR_FRAME);
	DefaultTrend = LEFT;
	TypeMorningStar = 1;
}

void MorningStar::Update(GameCamera *camera, int t)
{
	WeaponSprite->Update(t); 
	IsFinish = (WeaponSprite->_index == 3) + (WeaponSprite->_index == 7) + (WeaponSprite->_index == 11);
}

Box MorningStar::GetBox(GameCamera *camera)
{
	if (WeaponSprite->_index != 2 && WeaponSprite->_index != 6 && WeaponSprite->_index != 10) return Box(0, 0, 0, 0, 0, 0);
	float s = 0, X, Y, sw, sh;
	if (Trend == RIGHT)    
	{
		if (TypeMorningStar == 1) sw = (Size->FrameWidth)*0.8 - 30;
		if (TypeMorningStar == 2) sw = (Size->FrameWidth)*0.8 - 30;
		if (TypeMorningStar == 3) sw = (Size->FrameWidth) - 30;
		sh = (Size->FrameHeight)*0.5;
		X = x - Size->FrameWidth / 2 + 30;
	}
	if (Trend == LEFT)    
	{
		if (TypeMorningStar == 1) X = x + (Size->FrameWidth)*0.2;
		if (TypeMorningStar == 2) X = x + (Size->FrameWidth)*0.2;
		if (TypeMorningStar == 3) X = x;
		sw = (Size->FrameWidth)*0.8 - 30;
		sh = (Size->FrameHeight)*0.5 - 1;
		X = X - sw;
	}
	
	Y = y + Size->FrameHeight / 4;
	D3DXVECTOR2 pos = camera->Transform(X, Y);
	return Box(pos.x, pos.y, sw, sh, Vx, -Vy);
}

void MorningStar::DrawWeapon(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	int color = rand() % 255;
	PlayingMusic = color;
	WeaponSprite->SetARGB(255, rand() % 255, color, color / 2);
	if (Trend == DefaultTrend) WeaponSprite->Draw(pos.x, pos.y);
	else WeaponSprite->DrawFlipX(pos.x, pos.y);
}

void MorningStar::SetXY(float x, float y)
{
	this->x = x + 30 * Trend;
	this->y = y;
}

void MorningStar::SetTypeMorningStar(int i)
{
	if (i == -1)
	{
		if (TypeMorningStar < 3) TypeMorningStar++;
		return;
	}
	TypeMorningStar = i;
}

int MorningStar::GetTypeMorningStar()
{
	return TypeMorningStar;
}

void MorningStar::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x,sm_y,sm_trend);
	WeaponSprite->_index = TypeMorningStar * 4 - 4;
}
