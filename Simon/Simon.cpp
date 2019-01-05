#include "Simon.h"

Simon::Simon(float Vx, int iG, float x , float y , int Trend)
{
	Type = SIMON_OBJECT;
	Health = 20;
	this->Vx = Vx;
	this->Vy = NO_ACTION;
	SIMON_vx = Vx;
	Size = new GameTexture(SIMON_IMAGE, 8, 3, 24, ShowBox);
	TrSize = new GameTexture(SIMON_IMAGE_TR, 8, 3, 24, ShowBox);
	ObjectSprite = new GameSprite(Size, SIMON_FRAME);
	TrObjectSprite = new GameSprite(TrSize, SIMON_FRAME);

	SimonDeath = new GameSprite(new GameTexture("Resources/simondeath.png"), 0);
	this->x = x;
	this->y = y;
	this->weapon = new Weapon();
	this->Trend = Trend;

	AutoGo = NO_ACTION;
	IsOnStair = NO_ACTION;
	IsAttacking = NO_ACTION;
	IsSitting = NO_ACTION;
	IsFalling = NO_ACTION;
	IsJumping = NO_ACTION;
	IsGoing = NO_ACTION;
	PreAtk = NO_ACTION;
	WaitingCount = NO_ACTION;
	SimonFall = NO_ACTION;
	EndHurt = IS_ACTION;
	Invisible = NO_ACTION;

	if (iG) this->Go();

	Dx = x;
	Dy = y;
	DTrend = Trend;
	ResetSimon = NO_ACTION;

	BonusVx = NO_ACTION;
}

void Simon::Update(GameCamera *camera, int t)
{
	if (Water > NO_ACTION) Water--;
	if ((y < -20 || Health <= NO_ACTION) && !IsOpenTheGate)
	{
		ResetSimon = IS_ACTION;
		return;
	}

	if (IsOnStair == IS_ACTION)
	{
		if (IsAttacking == IS_ACTION)
		{
			ObjectSprite->Update(t);
			if (Trend*stairtrend == LEFT)
			{
				if (ObjectSprite->_index == NO_ACTION)
				{
					ObjectSprite->SelectIndex(12);
					IsAttacking = NO_ACTION;
				}
			}
			else
			if (ObjectSprite->_index == 21)
			{
				ObjectSprite->SelectIndex(10);
				IsAttacking = NO_ACTION;
			}
		}
		else 
		if (IsGoing == IS_ACTION)
		{
			x += Vx;
			y += Vy;
			ObjectSprite->Update(t);

			if (Trend*stairtrend == LEFT)
			{
				ObjectSprite->_index = ObjectSprite->_index % 2 + 12;
			}
			else
			{
				ObjectSprite->_index = ObjectSprite->_index % 2 + 10;
			}

			if ((Trend*stairtrend == LEFT))
			{
				if (y - y_upstair >= 45 && AutoGo == IS_ACTION)       
				{
					this->Stop();
					AutoGo = NO_ACTION;
				}
			}
			else
			{
				if (y_downstair - y >= NO_ACTION && AutoGo == IS_ACTION)
				{
					this->Stop();
					AutoGo = NO_ACTION;
				}
			}
		}
		else
		{
			if (Trend*stairtrend == LEFT) ObjectSprite->SelectIndex(12);
			else ObjectSprite->SelectIndex(10);
		}
		return;
	}

	if(IsAttacking == IS_ACTION)
	{
		ObjectSprite->Update(t);
		if (IsSitting == IS_ACTION)
		{
			if (ObjectSprite->_index > 17)
			{
				IsAttacking = NO_ACTION;
				this->Sit();
			}
		}
		else
		if (IsJumping == IS_ACTION)
		{
			Vx *= IsGoing;

			x += Vx;
			y += Vy;
			Vy = Vy - SIMON_GRAVITY;
			if (ObjectSprite->_index > 7)
			{
				IsAttacking = NO_ACTION;
				this->Fall();
			}
		}
		else
		if (ObjectSprite->_index > 7)
		{
			ObjectSprite->SelectIndex(SIMON_STOP);
			IsAttacking = NO_ACTION;
		}
	}
	else
	{
		if (IsJumping == IS_ACTION)
		{
			if (EndHurt) Vx *= IsGoing; else Vx = Vx_Hurt*HTrend*(Prevent == NO_ACTION);
			y += Vy;
			x += Vx;
			Vy = Vy - SIMON_GRAVITY;
			ObjectSprite->SelectIndex(SIMON_SIT);
			if (!EndHurt) ObjectSprite->SelectIndex(SIMON_HURT);
			if (Vy == NO_ACTION)
			{
				if (Start_Test_Jump)
				{
					this->Attack();
					test = 1;
				}
				this->Fall();
			}
		}
		else
		if (IsFalling == IS_ACTION)
		{
			if (EndHurt) Vx *= IsGoing; else Vx = Vx_Hurt*HTrend*(Prevent == NO_ACTION);
			x += Vx;
			y += Vy;
			Vy = Vy - SIMON_GRAVITY;
			ObjectSprite->SelectIndex(SIMON_STOP);
		}
		else
		if (IsGoing == IS_ACTION)
		{
			x += Vx;
			D3DXVECTOR2 pos = camera->Transform(x, y);
			if (pos.x <= Size->FrameWidth / 4 || pos.x > Game_ScreenWidth - Size->FrameWidth / 4) x -= Vx;
			ObjectSprite->Update(t);
			if (IsFalling == NO_ACTION && IsJumping == NO_ACTION) ObjectSprite->_index = ObjectSprite->_index % 4;
		}
		else
		if (IsSitting == IS_ACTION)
		{
			ObjectSprite->SelectIndex(SIMON_SIT);
		}
		else
		{
			if (test == 1 && Start_Test_Jump)
			{
				this->Attack();
				test = NO_ACTION;
			}
			ObjectSprite->SelectIndex(SIMON_STOP*(State>0) + 9 * (State == 0));
		}
	}

	x += BonusVx;
	if (!IsOpenTheGate)
	{
		if (x + Size->FrameWidth / 2 > camera->_maxSize && Trend == RIGHT) x = camera->_maxSize - Size->FrameWidth / 2 + 10;
		if (x - Size->FrameWidth / 2 < camera->_minSize && Trend == LEFT) x = camera->_minSize + Size->FrameWidth / 2 - 10;
		if (EndHurt == NO_ACTION)
		{
			if (x + Size->FrameWidth / 2 > camera->_maxSize) x = camera->_maxSize - Size->FrameWidth / 2 + 10;
			if (x - Size->FrameWidth / 2 < camera->_minSize) x = camera->_minSize + Size->FrameWidth / 2 - 10;
		}
	}
}

void Simon::DrawObject(GameCamera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Health <= 0)
	{
		if (Trend == LEFT) SimonDeath->Draw(pos.x, pos.y);
		else SimonDeath->DrawFlipX(pos.x, pos.y);
		return;
	}
	
	if (Invisible)
	{
		TrObjectSprite->_index = ObjectSprite->_index;
		if (Trend == LEFT) TrObjectSprite->Draw(pos.x, pos.y);
		else TrObjectSprite->DrawFlipX(pos.x, pos.y);
		return;
	}

	Object::DrawObject(camera);
}

int Simon::GetFrame()
{
	return SIMON_FRAME;
}

Box Simon::GetBox(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2 - 10, y + Size->FrameHeight / 2 - 10);
	return Box(pos.x, pos.y, Size->FrameWidth - 10, Size->FrameHeight - 10, Vx*(EndHurt == IS_ACTION) + Vx_Hurt*(EndHurt == 0), -Vy);
}

void Simon::Jump()
{
	if (IsAttacking == NO_ACTION && IsJumping == NO_ACTION && IsFalling == NO_ACTION)
	{
		if (IsJumping == NO_ACTION)
		{
			Vy = SIMON_VJUMP;
			ObjectSprite->SelectIndex(SIMON_SIT); 
			if (EndHurt == NO_ACTION)
			{
				ObjectSprite->SelectIndex(SIMON_HURT);
				Vx = Vx*HTrend;
			}
			Object::Jump();
		}
	}
}

void Simon::Hurt(int HTrend)
{
	if (IsHurting == NO_ACTION)
	{
		this->HTrend = HTrend > NO_ACTION ? RIGHT : LEFT;
		IsHurting = 50;
		EndHurt = NO_ACTION;
		SimonFall = NO_ACTION;
		Vx_Hurt = SIMON_vx;
		this->Jump();
	}
}

void Simon::StopHurt(float y)
{
	EndHurt = IS_ACTION;
	if (IsGoing == IS_ACTION) this->Go(); else this->StandUp();
	this->y = y;
	Vx = SIMON_vx;
	Vy = NO_ACTION;
}

void Simon::Fall()
{
	if (IsAttacking == NO_ACTION && IsJumping == IS_ACTION && IsFalling == NO_ACTION)
	{
		if (IsFalling == NO_ACTION)
		{
			Vy = -SIMON_VJUMP;
			ObjectSprite->SelectIndex(SIMON_STOP);
			Object::Fall();
		}
	}
}

void Simon::Sit()
{
	if (IsJumping == IS_ACTION || IsFalling == IS_ACTION) return;
	if (IsAttacking == NO_ACTION)
	{
		if (IsSitting == NO_ACTION) y = y - 20;
		ObjectSprite->SelectIndex(SIMON_SIT);
		Object::Sit();
	}
}

void Simon::StandUp()
{
	if (IsSitting == IS_ACTION) y = y + 20;
	ObjectSprite->SelectIndex(SIMON_STOP);
	Object::StandUp();
}

void Simon::Go()
{
	if (IsJumping == IS_ACTION || IsFalling == IS_ACTION) return;
	if (IsOnStair == IS_ACTION && IsAttacking == NO_ACTION)
	{
		Vx = SIMON_VX_STAIR*Trend;
		Vy = -SIMON_VY_STAIR*Trend*stairtrend;
		Object::Go();
		return;
	}
	if (IsAttacking == NO_ACTION)
	{
		if (IsSitting == IS_ACTION) this->StandUp();
		this->Vx = SIMON_vx*Trend;
		Object::Go();
		Prevent = NO_ACTION;
	}
}

void Simon::Attack(Weapon *w)
{
	if (EndHurt == NO_ACTION && (IsFalling == IS_ACTION || IsJumping == IS_ACTION)) return;
	if (IsAttacking == IS_ACTION) return;
	if (IsFalling == IS_ACTION) return;

	if (IsSitting == IS_ACTION)
	{
		ObjectSprite->SelectIndex(SIMON_SITATK);
	}
	else
	if (IsOnStair == IS_ACTION)
	{
		if (Trend*stairtrend == LEFT)
			ObjectSprite->_index = 21;
		else
			ObjectSprite->_index = 18;
	}
	else ObjectSprite->SelectIndex(SIMON_ATK);
	Object::Attack(w);
}

void Simon::Stop()
{
	if (IsOnStair == IS_ACTION && IsAttacking == NO_ACTION)
	{
		Object::Stop();
		return;
	}
	if (IsAttacking == NO_ACTION)
	{
		if (IsSitting == IS_ACTION) this->StandUp();
		Object::Stop();
		return;
	}
}

int Simon::IntoCastle(int t)
{
	this->Stop();
	ObjectSprite->SelectIndex(9);
	WaitingCount = WaitingCount + t;
	if (WaitingCount > 2200) return 1;
	return 0;
}

void Simon::StopFall(float y)
{
	IsAttacking = NO_ACTION;
	IsFalling = NO_ACTION;
	this->y = y;
	if (SimonFall) this->Sit();
	else
	if (IsGoing == IS_ACTION) this->Go();
	else this->StandUp();
	Vy = NO_ACTION;
}

void Simon::OutStair()
{
	Vy = NO_ACTION;
	Vx = SIMON_vx;
	IsOnStair = NO_ACTION;
	if (IsGoing == IS_ACTION) this->Go();
	else this->StandUp();
	this->ObjectSprite->_timeAni = 70;
}

void Simon::DownStair()
{
	Trend = stairtrend;
	Vx = SIMON_VX_STAIR*Trend;
	Vy = -SIMON_VY_STAIR*Trend*stairtrend;
	this->ObjectSprite->_timeAni = 100;
	IsSitting = NO_ACTION;
	IsJumping = NO_ACTION;
	IsFalling = NO_ACTION;
	IsOnStair = IS_ACTION;
}

bool Simon::GetOnStair()
{
	return IsOnStair;
}

void Simon::SetOnStair(bool i)
{
	IsOnStair = i;
}
void Simon::UpStair()
{
	if (Trend*stairtrend == RIGHT) Trend = -Trend;
	Vx = SIMON_VX_STAIR*Trend;
	Vy = -SIMON_VY_STAIR*Trend*stairtrend;
	this->ObjectSprite->_timeAni = 100;
	IsSitting = NO_ACTION;
	IsJumping = NO_ACTION;
	IsFalling = NO_ACTION;
	IsOnStair = IS_ACTION;
}


void Simon::UpdateResetPosition()
{
	Dx = x;
	Dy = y;
	DTrend = Trend;
}

void Simon::Resetsimon()
{
	x = Dx;
	y = Dy + 20;
	Trend = DTrend;
	Water = NO_ACTION;
	ResetSimon = NO_ACTION;
	Health = 20;
	IsOnStair = NO_ACTION;
	IsHurting = 50;
}
