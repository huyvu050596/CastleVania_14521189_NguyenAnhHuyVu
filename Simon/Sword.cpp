#include "Sword.h"

Sword::Sword()
{
	WeaponType = SWORD;
	Size = new GameTexture(SWORD_IMAGE);
	WeaponSprite = new GameSprite(Size, 0);
	DefaultTrend = RIGHT;
}

Sword::~Sword()
{
}

void Sword::Update(GameCamera *camera, int t)
{
	WeaponSprite->Update(t);
	x += Vx;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (pos.x > Game_ScreenWidth + 50 || pos.x < -50 || pos.y > Game_ScreenHeight + 20) IsFinish = IS_ACTION;
}

void Sword::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x, sm_y, sm_trend);
	Vx = SWORD_VX*Trend;
}
