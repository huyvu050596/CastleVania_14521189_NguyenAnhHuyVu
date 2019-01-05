#include "FireBall.h"

FireBall::FireBall()
{
	WeaponType = FIRE_BALL;
	Size = new GameTexture(FIREBALL_IMAGE);
	WeaponSprite = new GameSprite(Size, 0);
	DefaultTrend = LEFT;
}

FireBall::~FireBall()
{
}

void FireBall::Update(GameCamera *camera, int t)
{
	WeaponSprite->Update(t);
	x += Vx;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (pos.x > Game_ScreenWidth + 50 || pos.x < -50 || pos.y > Game_ScreenHeight + 20) IsFinish = IS_ACTION;
}

void FireBall::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x, sm_y + 16, sm_trend);
	Vx = FIREBALL_VX*Trend;
}
