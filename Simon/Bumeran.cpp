#include "Bumeran.h"

Bumeran::Bumeran()
{
	WeaponType = BUMERAN;
	Size = new GameTexture(BUMERAN_IMAGE, 3, 1, 3);
	WeaponSprite = new GameSprite(Size, BUMERAN_FRAME);
	DefaultTrend = RIGHT;
}

Bumeran::~Bumeran()
{
}

void Bumeran::Update(GameCamera *camera, int t)
{
	WeaponSprite->Update(t);
	x += Vx;
	Vx -= 1 * Trend;
	if ((Trend == RIGHT && Vx < 0) || (Trend == LEFT && Vx > 0)) BumeranColide = IS_ACTION;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (pos.x > Game_ScreenWidth + 50 || pos.x < -50 || pos.y > Game_ScreenHeight + 20) IsFinish = IS_ACTION;
}

void Bumeran::Create(float sm_x, float sm_y, int sm_trend)
{
	Weapon::Create(sm_x, sm_y, sm_trend);
	Vx = BUMERAN_VX*Trend;
}

void Bumeran::BumeranBack()
{
	Trend *= LEFT;
	Vx = BUMERAN_VX*Trend;
	BumeranColide = IS_ACTION;
}
