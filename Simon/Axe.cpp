#include "Axe.h"

Axe::Axe()
{
	WeaponType = AXE;
	Size = new GameTexture(AXE_IMAGE, 4, 1, 4);
	WeaponSprite = new GameSprite(Size, AXE_FRAME);
	DefaultTrend = RIGHT;
}

Axe::~Axe()
{
}

void Axe::Update(GameCamera *camera, int t)
{
	WeaponSprite->Update(t);
	x += Vx;
	y += Vy;
	Vy -= AXE_GRAVITY;

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (pos.x > Game_ScreenWidth + 50 || pos.x < -50 || pos.y > Game_ScreenHeight + 20) IsFinish = IS_ACTION;
}

void Axe::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x, sm_y, sm_trend);
	Vx = AXE_VX*Trend;
	Vy = AXE_VY;
}
