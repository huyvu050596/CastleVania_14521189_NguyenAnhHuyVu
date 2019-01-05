#include "Bottle.h"

Bottle::Bottle()
{
	WeaponType = BOTTLE;
	Size = new GameTexture(BOTTLE_IMAGE, 3, 1, 3);
	WeaponSprite = new GameSprite(Size, BOTTLE_FRAME);
	DefaultTrend = RIGHT;
}

Bottle::~Bottle()
{
}

void Bottle::Update(GameCamera *camera, int t)
{
	x += Vx;
	y += Vy;
	Vy -= BOTTLE_GRAVITY;
	if (IsBoom == NO_ACTION)
	{
		WeaponSprite->SelectIndex(0);
	}
	else
	{
		Vy = NO_ACTION;
		Vx = NO_ACTION;
		WaitingTime += t;
		if (WaitingTime > 100)
		{
			WeaponSprite->Update(t);
			if (WeaponSprite->_index == 0) WeaponSprite->SelectIndex(1);
			if (WaitingTime > 700) IsFinish = IS_ACTION;
		}
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (pos.x > Game_ScreenWidth + 50 || pos.x < -50 || pos.y > Game_ScreenHeight) IsFinish = IS_ACTION;
}

void Bottle::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x, sm_y, sm_trend);
	Vx = BOTTLE_VX*Trend;
	Vy = BOTTLE_VY;
	IsBoom = NO_ACTION;
	WaitingTime = NO_ACTION;
}

void Bottle::Boom()
{
	if (Vy < NO_ACTION) IsBoom = 1;
}

void Bottle::DrawWeapon(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == DefaultTrend) WeaponSprite->Draw(pos.x, pos.y);
	else WeaponSprite->DrawFlipX(pos.x, pos.y);

	if (WeaponSprite->_index > 0)
	{
		WeaponSprite->Draw(pos.x - Size->FrameWidth/2, pos.y);
		WeaponSprite->Draw(pos.x + Size->FrameWidth/2, pos.y);
	}
}
