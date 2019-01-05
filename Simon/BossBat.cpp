#include "BossBat.h"

BossBat::BossBat(float x, float y, int fit)
{
	Type = 26;
	Vx = 0;
	Vy = 0;

	Size = new GameTexture(BOSSBAT_IMAGE, 3, 1, 3, ShowBox);
	ObjectSprite = new GameSprite(Size, BOSSBAT_FRAME_NRM);

	this->x = x;
	this->y = y;
	
	IsGoing = 0;
	WaitingTime = 0;

	srand(time(NULL));
	WT = rand() % (1500 - 1000 + 1) + 1000;

	Status = 0;
	if (fit) FitPosision();

	Health = 20;
	y_before = Dy;
	
	this->Dx = this->x;
	this->Dy = this->y;
	this->DTrend = this->Trend;
	this->DHealth = this->Health;
}

void BossBat::Update(GameCamera *camera,int t)
{
	if (Status == 0)   
	{
		ObjectSprite->SelectIndex(BOSSBAT_STOP);
		return;
	}

	ObjectSprite->Update(t);

	if (ObjectSprite->_index == 0) ObjectSprite->SelectIndex(1);

	if (Status == 1) 
	{
		ObjectSprite->_timeAni = BOSSBAT_FRAME_NRM;
		WaitingTime += t;
		if (WaitingTime > WT)
		{
			WaitingTime = 0;
			Status = 2;
		}
	}
	else
	if (Status == 2)
	{
		ObjectSprite->_timeAni = BOSSBAT_FRAME_ATK;
		x1 = x - sm_x;
		if (x1 == 0) x1 = 1;
		y1 = y - sm_y;
		Vx = -x1 / 40;
		a = y1 / (x1*x1);
		Status = 3;
		y_before = y;
	}
	else
	if (Status == 3) 
	{
		x += Vx;
		y = (x - sm_x)*(x - sm_x)*a + sm_y;
	
		if (y >= y_before || x +Size->FrameWidth/2 >= camera->viewport.x + Game_ScreenWidth || x - Size->FrameWidth / 2 <= camera->viewport.x)
		{
			Status = 4;
			ObjectSprite->_timeAni = BOSSBAT_FRAME_NRM;
		}
		y_before = y;
	}
	else
	if (Status == 4)
	{
		WaitingTime += t;
		if (WaitingTime > 300)
		{
			WaitingTime = 0;
			Status = 5;
			srand(time(NULL));
			WT = rand() % (1500 - 1000 + 1) + 1000;
		}
	}
	else
	if (Status == 5)
	{
		ObjectSprite->_timeAni = BOSSBAT_FRAME_ATK;
		x2 = FindX(camera);
		y2 = FindY(camera);
		x1 = x - x2;
		y1 = y - y2;
		Vx = -x1 / 40;
		a = y1 / x1;
		Status = 6;
	}
	else
	if (Status == 6)
	{
		x += Vx;
		y = (x - x2)*a + y2;
		if (y >= y2)
		{
			Status = 1;
			ObjectSprite->_timeAni = BOSSBAT_FRAME_NRM;
			srand(time(NULL));
			WT = rand() % (1500 - 1000 + 1) + 1000;
		}
	}
}

void BossBat::GetSMPositionForBoss(float x, float y, int Trend)
{
	if (Status >= 2) return;
	sm_x = x;
	sm_y = y;
	sm_Trend = Trend;
}

float BossBat::FindX(GameCamera *camera)
{
	srand(time(NULL));
	int RandomX = rand() % 3; 
	if (RandomX == 0) return camera->viewport.x + Game_ScreenWidth / 10;
	if (RandomX == 1) return camera->viewport.x + Game_ScreenWidth / 2;
	if (RandomX == 2) return camera->viewport.x + 8*Game_ScreenWidth / 10;
}

float BossBat::FindY(GameCamera *camera)
{
	srand(time(NULL));
	int RandomY = rand() % 3;
	if (RandomY == 0) return camera->viewport.y - Game_ScreenHeight / 2;
	if (RandomY == 1) return camera->viewport.y - 3 * Game_ScreenHeight / 5;
	if (RandomY == 2) return Dy;
}

void BossBat::ResetPosition()
{
	WaitingTime = 0;

	srand(time(NULL));
	WT = rand() % (1500 - 1000 + 1) + 1000;

	Status = 0;
	y_before = Dy;
	
	Object::ResetPosition();
}

void BossBat::Go()
{
	Object::Go();
	Status = 1;
	ObjectSprite->_timeAni = 50;
	ObjectSprite->SelectIndex(1);
}