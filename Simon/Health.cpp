#include "Health.h"

Health::Health()
{
	this->x = 97;
	this->y[Simon] =  38;
	this->y[Boss] = 61;

	Size = new GameTexture(IMAGE_FILE, 3, 1, 3);
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = 1;
	Type = 32;
}

Health::~Health()
{
}

void Health::DrawObject(int HealthSimon, int HealthBoss)
{
	HealthSimon = HealthSimon >= 0 ? HealthSimon : 0;
	HealthBoss = HealthBoss >= 0 ? HealthBoss : 0;
	for (int i = 0; i < HealthSimon; i++) ObjectSprite->DrawIndex(Simon, x + i*(Size->FrameWidth), y[Simon]);
	for (int i = HealthSimon; i<MAX_HEALTH; i++) ObjectSprite->DrawIndex(Empty, x + i*(Size->FrameWidth), y[Simon]);
	for (int i = 0; i<HealthBoss; i++) ObjectSprite->DrawIndex(Boss, x + i*(Size->FrameWidth), y[Boss]);
	for (int i = HealthBoss; i<MAX_HEALTH; i++) ObjectSprite->DrawIndex(Empty, x + i*(Size->FrameWidth), y[Boss]);
}
