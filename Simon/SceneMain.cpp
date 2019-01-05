#include "SceneMain.h"
#include <string>

string FullNumber(int a, int max)
{
	string result = to_string(a);
	for (int i = to_string(a).length(); i < max; i++)
	{
		result = "0" + result;
	}
	return result;
}

SceneMain::SceneMain(int _nCmdShow) : CGame(_nCmdShow)
{
}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->ColorFill(Game_BackBuffer, NULL, D3DCOLOR_XRGB(number_0, number_0, number_0));

	if (State > STEP_0 && simon->ResetSimon)
	{
		if (WaitingTime == number_0) Sound->PlaySound(SimonDie);
		if (WaitingTime < TIME_ANI_600) WaitingTime += t;
		else
		{
			WaitingTime = number_0;
			ResetResource(d3ddv);
		}
	}

	if (EatBall && !Calculating) CalculatorScore();

	if (Calculating) CalculatorScore();
	else
	{
		DetectCollision(d3ddv, t);
		UpdateObjects(t);
	}
	
	Game_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (State > STEP_0) DrawBoard(d3ddv);

	DrawObjects(d3ddv);

	Game_SpriteHandler->End();
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	//Dang o intro vao play game
	if (State == -STEP_1)
	{
		if (IsKeyDown(DIK_RETURN))
		{
			State = STEP_0;
			Scene0();
			return;
		}
		return;
	}
	//Neu trong cac trang thai sao thi khong cho bam nut.
	if (SceneEnding) return;
	if (State == STEP_0) return;
	if (IsOpenTheGate) return;
	if (UpStairPre) return;
	if (DownStairPre) return;
	if (simon->AutoGo) return;
	if (simon->GetAlive() <= number_0) return;

	//Simon di tren cau thang
	if (simon->GetOnStair())
	{
		//Di chuyen camera theo Simon
		MoveCamera(IsKeyDown(DIK_LEFT), IsKeyDown(DIK_RIGHT), IsKeyDown(DIK_UP), IsKeyDown(DIK_DOWN));
		//Simon dang huong sang trai
		if (simon->stairtrend == LEFT)
		{
			if (IsKeyDown(DIK_LEFT) || IsKeyDown(DIK_DOWN))
			{
				simon->MoveLeft();
				simon->Go();
			}
			if (IsKeyDown(DIK_RIGHT) || IsKeyDown(DIK_UP))
			{
				simon->MoveRight();
				simon->Go();
			}
		}
		//Simon dang huong sang phai
		else 
		{
			if (IsKeyDown(DIK_RIGHT) || IsKeyDown(DIK_DOWN))
			{
				simon->MoveRight();
				simon->Go();
			}
			if (IsKeyDown(DIK_LEFT) || IsKeyDown(DIK_UP))
			{
				simon->MoveLeft();
				simon->Go();
			}
		}
		//Check simon dung im
		if (!IsKeyDown(DIK_LEFT) && !IsKeyDown(DIK_DOWN) && !IsKeyDown(DIK_RIGHT) && !IsKeyDown(DIK_UP))
		{
			simon->Stop();
		}
		//Check simon danh tren cau thang
		if (IsKeyDown(DIK_A))
		{
			simon->Attack(Weapons.at(0));
			if (simon->GetAttacking()) Sound->PlaySound(Whip);
		}
		return;
	}
	//Simon su dung vu khi phu de attack
	if (IsKeyDown(DIK_A) && IsKeyDown(DIK_UP) && simon->GetAttacking() == NO_ACTION)
	{
		if (Weapon2 < number_0 || Weapons.size() > Shot || Heart == number_0 || Stopwatch_Time > NO_ACTION) return; //simon->Attack(Weapons.at(0));
		else
		{
			if (Weapon2 == STOPWATCH_ITEM)
			{
				if (Heart >= number_5)
				{
					Sound->LoopSound(WatchWeapon);
					Heart -= number_5;
					Stopwatch_Time = IS_ACTION;
					return;
				}
			}
			if (Weapon2 == SWORD) Weapons.push_back(new Sword());
			if (Weapon2 == BOTTLE) Weapons.push_back(new Bottle());
			if (Weapon2 == AXE) Weapons.push_back(new Axe());
			if (Weapon2 == BUMERAN) Weapons.push_back(new Bumeran());
			simon->Attack(Weapons.back());

			if (simon->GetAttacking()) Heart--;
		}
		if (simon->GetAttacking()) Sound->PlaySound(Whip);
	}
	//Khong cho simon tu dong di chuyen sang trai/phai
	if (!(IsKeyDown(DIK_LEFT)) && !(IsKeyDown(DIK_RIGHT)) && !(simon->AutoGo))
	{
		simon->Stop();
	}
	//Simon qua trai
	if (IsKeyDown(DIK_LEFT) && !(IsKeyDown(DIK_RIGHT)))
	{
		simon->MoveLeft();
		simon->Go();
	}
	//Simon qua phai
	if (IsKeyDown(DIK_RIGHT) && !(IsKeyDown(DIK_LEFT)))
	{
		simon->MoveRight();
		simon->Go();
	}
	//Simon di len
	if (IsKeyDown(DIK_UP))
	{
		simon->IsUp = IS_ACTION;
	}
	else simon->IsUp = NO_ACTION;
	//Simon di xuong
	if (IsKeyDown(DIK_DOWN))
	{
		simon->IsDown = IS_ACTION;
	}
	else simon->IsDown = NO_ACTION;
	//Simon ngoi
	if (IsKeyDown(DIK_DOWN) && !(IsKeyDown(DIK_S)))
	{
		simon->Sit();
	}
	//Simon danh binh thuong
	if (IsKeyDown(DIK_A))
	{
		simon->Attack(Weapons.at(0));
		if (simon->GetAttacking()) Sound->PlaySound(Whip);
	}
	//Simon nhay
	if (IsKeyDown(DIK_S) && !(IsKeyDown(DIK_DOWN)))
	{
		simon->Jump();
		simon->SimonFall = NO_ACTION;
	}
	//1 Kiem
	if (IsKeyDown(DIK_1))
	{
		Weapon2 = SWORD;
	}
	//2 Boom
	if (IsKeyDown(DIK_2))
	{
		Weapon2 = BOTTLE;
	}
	//3 Bua
	if (IsKeyDown(DIK_3))
	{
		Weapon2 = AXE;
	}
	//4 Bumeran
	if (IsKeyDown(DIK_4))
	{
		Weapon2 = BUMERAN;
	}
	//5 Dong ho ngung dong
	if (IsKeyDown(DIK_5))
	{
		Weapon2 = STOPWATCH_ITEM;

	}
	//Cho ITEM tiep theo rot chu thap
	if (IsKeyDown(DIK_6))
	{
		NextItem = CROSS_ITEM;
	}
	// Set heart 99
	if (IsKeyDown(DIK_7))
	{
		Heart = 99;
		NextItem = POTION_ITEM;
	}
	//Set heart mang
	if (IsKeyDown(DIK_8))
	{
		RevivalNumber = 99;
	}
	//Danh lien tiep 2 phat
	if (IsKeyDown(DIK_9))
	{
		Shot = STEP_2;
	}
	//Danh lien tiep 3 phat
	if (IsKeyDown(DIK_0))
	{
		Shot = STEP_3;
	}
	//Set full mau
	if (IsKeyDown(DIK_O))
	{
		simon->SetAlive(-20);
	}
	//Set chet ngay lap tuc
	if (IsKeyDown(DIK_P))
	{
		simon->SetAlive(20);
	}
	// Boss doi X: 5183, Y: 445
	if (IsKeyDown(DIK_K))
	{
		State = STEP_2;
		Scene2();
		simon->SetX(5183);
		simon->SetY(600);
		camera->SetSizeMap(camera->viewport.x, Game_MapWidth);
	}
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	//Load audio cho game
	Sound = new GameAudio();
	Sound->dsound = new GSoundManager();
	Sound->Init_DirectSound(Game_hWnd);

	MusicState1 = Sound->LoadSound("Resources/music/Stage_01_Vampire_Killer.wav");
	MusicState2 = Sound->LoadSound("Resources/music/Stage_04_Stalker.wav");
	BossBattle = Sound->LoadSound("Resources/music/Boss_Battle_Poison_Mind.wav");
	GameStart = Sound->LoadSound("Resources/music/Game_Start_Prologue.wav");
	SimonDie = Sound->LoadSound("Resources/music/Life_Lost.wav");
	Menu = Sound->LoadSound("Resources/music/Menumusic.wav");

	CollectItem = Sound->LoadSound("Resources/sound/collectitem.wav");
	CollectWeapon = Sound->LoadSound("Resources/sound/collectweapon.wav");
	Fall = Sound->LoadSound("Resources/sound/falling.wav");
	FallWater = Sound->LoadSound("Resources/sound/fallingdownwatersurface.wav");
	Hit = Sound->LoadSound("Resources/sound/hit.wav");
	OpenDoor = Sound->LoadSound("Resources/sound/opendoor.wav");
	Whip = Sound->LoadSound("Resources/sound/usingwhip.wav");
	CalScore1 = Sound->LoadSound("Resources/sound/DesTime.wav");
	CalScore2 = Sound->LoadSound("Resources/sound/decreaseweaponusepoint.wav");
	ScenceClear = Sound->LoadSound("Resources/music/Stage_Clear.wav");
	HolyCross = Sound->LoadSound("Resources/sound/holycross.wav");
	HolyWater = Sound->LoadSound("Resources/sound/holywater.wav");
	Potion = Sound->LoadSound("Resources/sound/potion.wav");
	WatchWeapon = Sound->LoadSound("Resources/sound/watch.wav");
	SimonHurt = Sound->LoadSound("Resources/sound/hurt.wav");
	TimeUp = Sound->LoadSound("Resources/sound/TimeUp.wav");
	EndScence1 = Sound->LoadSound("Resources/sound/endScence1.wav");
	
	//Load Font de ve ve cac doi tuong tren board
	Arial = new GameFont();
	blackboard = new BlackBoard();
	weaponboard = new WeaponBoard();
	shotboard = new ShotBoard();
	health = new Health();
	
	//Khoi tao cac gia tri default can thiet cho game
	BossId = -IS_ACTION;//-1 
	Weapon2 = -IS_ACTION;//-1
	Shot = STEP_1;//Bao nhieu lan attack
	RuningHolyCross = NO_ACTION;//
	CollectMorningStar = NO_ACTION;//Nhat vu khi
	Objects.clear();
	Weapons.clear();
	Weapons.push_back(new MorningStar());//Khoi tao vu khi ban dau
	CamObj = new CameraObject(); //Khoi tao camera
	WaitingTime = NO_ACTION;
	Stopwatch_Time = NO_ACTION;
	Calculating = NO_ACTION;

	Heart = number_5;
	RevivalNumber = number_5;

	if (State == -num_1) LoadMainMenu();
	if (State == STEP_0) Scene0();
	if (State == STEP_1) Scene1();
	if (State == STEP_2) Scene2();
}

void SceneMain::ResetResource(LPDIRECT3DDEVICE9 d3ddv)
{
	//Neu dang dau boss se play source box, state2 = boss doi
	if (BossAction)
	{
		Sound->StopSound(BossBattle);
		if (State == STEP_2) Sound->PlaySound(MusicState1);
	}

	RevivalNumber--;//Giam mang cua Simon di 1 mang

	if (RevivalNumber == 0)
	{
		if (State <= 2) Sound->StopSound(MusicState1);
		LoadMainMenu();
		return;
	}
	// Reset cac khoi tao default
	simon->Resetsimon();
	Weapon2 = -IS_ACTION;//-1
	Shot = STEP_1;
	BossAction = NO_ACTION;
	BossId = -IS_ACTION;
	EatBall = NO_ACTION;
	RuningHolyCross = NO_ACTION;
	Heart = number_5;

	SceneEnding = NO_ACTION;

	Floor = SaveFloor;

	for (int i = number_0; i < Objects.size(); i++)
	{
		if (CheckObject(Objects.at(i)->GetType()) == IS_ACTION)
		{
			Objects.at(i)->ResetPosition();
			Objects.at(i)->Health = Objects.at(i)->DHealth;
		}
	}
	//Reset quadtree and clear cac doi tuong
	QuadtreeRender->ResetTake(1);

	Enemy.clear();

	camera->viewport.x = DVx;
	camera->viewport.y = DVy;
	camera->_minSize = DMinVx;
	camera->_maxSize = DMaxVx;

	SimonAfter = simon->GetX();
	simon->SimonFall = NO_ACTION;

	Weapons.clear();
	Weapons.push_back(new MorningStar());
}

void SceneMain::UpdateObjects(int t)
{
	//Khi su dung dong ho ngung dong
	if (Stopwatch_Time > NO_ACTION)
	{
		if (Stopwatch_Time == TIME_ANI_150)
		{
			Stopwatch_Time = NO_ACTION;
			Sound->StopSound(WatchWeapon);
		}
		else Stopwatch_Time++;
	}
	//Simon tan hinh
	if (Simon_Invisi_Time > NO_ACTION)
	{
		if (Simon_Invisi_Time == TIME_ANI_150)
		{
			Simon_Invisi_Time = NO_ACTION;
			simon->Invisible = NO_ACTION;
		}
		else Simon_Invisi_Time++;

		if (Simon_Invisi_Time == TIME_ANI_150) Sound->PlaySound(Potion);
	}
	//Simon an thap gia 
	if (RuningHolyCross || State == -STEP_1) return;

	SimonBefore = SimonAfter;

	if (CollectMorningStar == STEP_0) simon->Update(camera, t);
	else
	{
		CollectMorningStar++;
		if (CollectMorningStar == 21) CollectMorningStar = STEP_0;
	}

	SimonAfter = simon->GetX();
	//Set camera cho simon
	if (State != STEP_0 && !IsOpenTheGate && BossAction == NO_ACTION)
	{
		camera->SetFolowPos(simon->GetX(), simon->GetY());
		camera->SetVCam(SimonAfter - SimonBefore, simon->GetVy());
		camera->UpdateCamera();
	}

	if (BossAction && BossId != -IS_ACTION)
	{
		if (Enemy.at(BossId)->GetAlive() && simon->GetJumping() == NO_ACTION && simon->GetFalling() == NO_ACTION)
			//Cho boss huong ve simon
			Enemy.at(BossId)->GetSMPositionForBoss(simon->GetX(), simon->GetY(), simon->GetTrend());
	}

	for (int i = number_0; i < ObjectsRender.size(); i++)
	{
		if (ObjectsRender.at(i)->GetAlive())
		{
			if (CheckObject(ObjectsRender.at(i)->GetType()) != IS_ACTION) ObjectsRender.at(i)->Update(camera, t);
			else if (Stopwatch_Time == STEP_0) ObjectsRender.at(i)->Update(camera, t);
		}
	}
	//Update cac hieu uong co trong vector* Effect, Item, Weapons, EnemyWeapons
	for (int i = number_0; i < Effects.size(); i++)
	{
		Effects.at(i)->Update(camera, t);
	}
	for (int i = number_0; i < Items.size(); i++)
	{
		Items.at(i)->Update(camera, t);
	}

	for (int i = number_0; i < Weapons.size(); i++)
	{
		if (Weapons.at(i)->GetFinish() == NO_ACTION) Weapons.at(i)->Update(camera, t);
	}

	for (int i = NO_ACTION; i < EnemyWeapons.size(); i++)
	{
		if (EnemyWeapons.at(i)->GetFinish() == NO_ACTION) EnemyWeapons.at(i)->Update(camera, t);
	}
}

void SceneMain::DetectCollision(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (State == -num_1) return;

	float nx, ny;
	float CollideTime;
	///Cho va cham vao gate intro game
	if (State == STEP_0)
	{
		if ((Collide(simon->GetBox(camera), ObjectsRender.at(0)->GetBox(camera), CollideTime, nx, ny) > NO_COLLIDE) || simon->WaitingCount > STEP_0)
		{
			//Simon dung gate va bat dau vao state 1;
			if (simon->IntoCastle(t))
			{
				State = STEP_1;
				Sound->StopSound(MusicState1);
				Scene1(); 
			}
		}
		return;
	}
	//Set camera cho game
	CamObj->SetCameraObj(camera->viewport.x, camera->viewport.y - AutoFit, Game_ScreenWidth, SIZE_384); //384

	ObjectsRender.clear();
	//Khoi tao cac ObjectRender voi Cammera
	if (State != STEP_0)
	{
		QuadtreeRender->ResetTake();
		QuadtreeRender->Retrieve(ObjectsRender, CamObj, number_0, camera);
	}
	//Check Enemies va push sao mang
	for (int i = number_0; i < Enemy.size(); i++)
	{
		if (Enemy.at(i)->GetAlive() && !BossAction) ObjectsRender.push_back(Enemy.at(i));
		if ((Enemy.at(i)->GetType() == BOSS_BAT) && BossAction)
		{
			if (Enemy.at(i)->GetAlive()) ObjectsRender.push_back(Enemy.at(i));
			else Win = IS_ACTION;
		}
	}

	Enemy.clear(); 
	Ground.clear();
	Invisi.clear(); 

	BossId = -1;
	
	//Duyet mang ObjectsRender push cac Object.
	for (int i = number_0; i < ObjectsRender.size(); i++)
	{
		if (CheckObject(ObjectsRender.at(i)->GetType()) == IS_ACTION)
		{
			Enemy.push_back(ObjectsRender.at(i));
			if (BossAction && ObjectsRender.at(i)->GetType() == BOSS_BAT) BossId = Enemy.size() - 1;
		}
		if (ObjectsRender.at(i)->GetType() == BRICK)
		{
			Ground.push_back(ObjectsRender.at(i));
		}
		if (CheckObject(ObjectsRender.at(i)->GetType()) == NO_ACTION)
		{
			Invisi.push_back(ObjectsRender.at(i));
		}
	}
	/////////////////////////////
	vector<Effect*>::iterator eff;
	for (eff = Effects.begin(); eff != Effects.end(); )
	{
		if ((*eff)->GetFinish() == number_5)
		{
			eff = Effects.erase(eff);
		}
		else ++eff;
	}
	////////////////////////////
	vector<Item*>::iterator its;
	for (its = Items.begin(); its != Items.end(); )
	{
		if ((*its)->GetFinish())
		{
			its = Items.erase(its);
		}
		else ++its;
	}
	/////////////////////////////
	vector<Weapon*>::iterator wps;
	for (wps = Weapons.begin(); wps != Weapons.end(); )
	{
		if ((*wps)->GetFinish() && (*wps)->GetType() != NO_ACTION)
		{
			wps = Weapons.erase(wps);
		}
		else ++wps;
	}
	//Ket thuc Step1
	if (State == STEP_1 && SceneEnding)
	{
		if (EndScene1())
		{
			State = STEP_2;
			Scene2();
		}
		return;
	}
	//Cham mo cua
	if (IsOpenTheGate)
	{
		OpenTheGate();
		return;
	}
	//Chuan bi di len cau thang
	if (UpStairPre)
	{
		GoUpStair(simon->x_upstair, simon->y_upstair, simon->stairtrend);
		return;
	}
	//Chuan bi di xuong cau thang
	if (DownStairPre)
	{
		GoDownStair(simon->x_downstair, simon->y_downstair, simon->stairtrend);
		return;
	}
	//Check va chuan bi cho Enemy chay khi camera den
	for (int i = number_0; i < Enemy.size(); i++)
	{
		if (!BossAction)
		{
			D3DXVECTOR2 pos = camera->Transform(Enemy.at(i)->GetX(), Enemy.at(i)->GetY());
			if (pos.x >= number_0 && pos.x <= Game_ScreenWidth + 30 && pos.y >= number_0 && pos.y <= Game_ScreenHeight)
			{
				//Neu Enemy la boss doi thi thuc hien action
				if (Enemy.at(i)->GetType() == BOSS_BAT && Enemy.at(i)->GetX() < simon->GetX())
				{
					Enemy.at(i)->Go();
					BossAction = IS_ACTION;
					camera->viewport.x = Game_MapWidth - Game_ScreenWidth;
					camera->SetSizeMap(Game_MapWidth - Game_ScreenWidth, Game_MapWidth);
					BossId = i;
					Sound->StopSound(MusicState1);
					Sound->LoopSound(BossBattle);
					break;
				}
				//New Enemy la con bao' thi chay
				if (Enemy.at(i)->GetType() == PANTHER && abs(Enemy.at(i)->GetX() - simon->GetX()) <= 150)
				{
					Enemy.at(i)->Go();
				}
				//con bao' roi rot suong
				else if (Enemy.at(i)->GetType() == PANTHER) Enemy.at(i)->Fall();

				//Neu la nguoi ca thi bat lua~
				if (Enemy.at(i)->GetType() == FISH_MAN && Enemy.at(i)->CreateWeapon())
				{
					EnemyWeapons.push_back(new FireBall());
					Enemy.at(i)->Attack(EnemyWeapons.back());
					Enemy.at(i)->SetCreateWeapon();
				}
				//Neu la cac Enemy con lai thi cho chay
				if (Enemy.at(i)->GetType() != BOSS_BAT && Enemy.at(i)->GetType() != PANTHER) Enemy.at(i)->Go();
			}
		}

	}

	//Khoi tao cac doi tuong ObjectRender theo co the va cham camera tren Quadtree
	QuadtreeCollide = new QuadTree(0, camera->viewport.x, camera->viewport.y - AutoFit - SIZE_384, Game_ScreenWidth, SIZE_384, ObjectsRender);
	QuadtreeCollide->ResetTake();
	//Insert cac doi tuong ObjectRender
	for (int i = 0; i < ObjectsRender.size(); i++) QuadtreeCollide->Insert(i, 0);


	vector<Object*> ListObj;
	vector<Object*>::iterator it;

	ListObj.clear();
	
	QuadtreeCollide->ResetTake();
	//Khoi tao cac Obj co the va cham voi simon theo camera
	QuadtreeCollide->Retrieve(ListObj, simon, 0, camera, 0);

	GoOnBrick = false;

	for (it = ListObj.begin(); it != ListObj.end(); it++)
	{
		//Cham cua man 1
		if ((*it)->GetType() == INVISIBLE_OBJECT && !simon->GetFalling() && !simon->GetJumping())
		{
			if ((Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny) > NO_COLLIDE))
			{
				if (State == STEP_1) EndScene1();
				Sound->PlaySound(EndScence1);
			}
		}

		//Simon cham nuoc
		if ((*it)->GetType() == WATER_OBJECT && simon->Water == NO_ACTION)
		{
			if ((Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny) > NO_COLLIDE))
			{
				Effects.push_back(new Water(simon->GetX(), (*it)->GetY()));
				simon->Water = 50;
				Sound->PlaySound(FallWater);
			}
		}

		//Simon cham vao Object len cau thang
		if ((*it)->GetType() == UP_STAIR_OBJECT)
		{
			int IsCollide = Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
			if (IsCollide)
			{
				simon->x_upstair = (*it)->GetX();
				simon->y_upstair = (*it)->GetY();
				simon->stairtrend = (*it)->GetTrend();

   				if (simon->IsUp && !(simon->GetJumping()) && !(simon->GetFalling()) && (simon->GetX() != simon->x_upstair) && (simon->GetY() > (*it)->GetY()))
				{
					GoUp = IS_ACTION;
					UpStairPre = true;
					StepUpStair = STEP_0;
				}
				else
					if (simon->GetOnStair() && (simon->GetTrend()*simon->stairtrend))
					{
						simon->OutStair();
						GoOnBrick = IS_ACTION;
						StepUpStair = STEP_0;
						simon->SetY(simon->y_upstair - 5 + 32);//5 on start, 32 height/width
					}
			}
		}

		//Simon cham vao Object xuong cau thang
		if ((*it)->GetType() == DOWN_STAIR_OBJECT)
		{
			int IsCollide = Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
			if (IsCollide)
			{
				simon->x_downstair = (*it)->GetX();
				simon->y_downstair = (*it)->GetY();
				simon->stairtrend = (*it)->GetTrend();

				if (simon->IsDown && !(simon->GetJumping()) && !(simon->GetFalling()) && (simon->GetX() != simon->x_downstair) && (simon->GetY() > (*it)->GetY()))
				{
					GoDown = IS_ACTION;
					DownStairPre = true;
					StepDownStair = STEP_0;
				}

				if (simon->GetOnStair() && GoUp && simon->GetTrend()*simon->stairtrend == LEFT)
				{
					if (simon->GetY() - 30 >= simon->y_downstair)
					{
						simon->OutStair();
						GoOnBrick = IS_ACTION;
						StepDownStair = STEP_0;
						simon->SetY(simon->y_downstair - 5 + 32);
					}
				}
			}
		}

		//Va cham vao gach, cau thang 2
		if ((*it)->GetType() == BRICK || (*it)->GetType() == STAIR2)
		{
			int IsCollide = Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
			if (IsCollide)
			{
				//Va cham vao gach ben trai or phai
				if ((*it)->GetType() == BRICK && (IsCollide == COLLIDE_LEFT || IsCollide == COLLIDE_RIGHT) && !(simon->GetOnStair()))
				{
					if (simon->GetJumping() && simon->GetMoving() && simon->GetY() + simon->GetHeight() / num_2 >= (*it)->GetY() + (*it)->GetHeight() / num_2 - num_20)
					{
						simon->SetX(simon->GetX() + simon->GetVx());
						simon->Stop();
					}
					else
						if (simon->GetY() - simon->GetHeight() / num_2 + num_10 <= (*it)->GetY())
						{
							simon->Stop();
							simon->Vx_Hurt = NO_ACTION;
						}
				}

				//Da cat va chuan bi va cham phia tren
				if (IsCollide == COLLIDE_TOP)
				{
					if (simon->GetY() > (*it)->GetY())
					{
						int setY = (*it)->GetY() + (*it)->GetHeight() / num_2 + simon->GetHeight() / num_2 - num_16 * ((*it)->GetType() != STAIR2);
						simon->StopFall(setY);
					}
					else
					{
						simon->StopFall((*it)->GetY() + (*it)->GetHeight() / num_2 + simon->GetHeight() / num_2);
					}
					if (simon->SimonFall) Sound->PlaySound(Fall);
				}

				if (IsCollide != COLLIDE_BOTTOM)
				{
					GoOnBrick = true;
					//simon->BonusVx = number_0;
				}
			}
		}

		//Va cham vao cua~
		if ((*it)->GetType() == DOOR)
		{
			int IsCollide = Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
			if (IsCollide)
			{
				if (!simon->GetFalling() && !simon->GetJumping())
				{
					simon->Stop();
					if (State == STEP_2) simon->SetTrend(RIGHT); else  simon->SetTrend(LEFT);
					XToOpen = camera->viewport.x + Game_ScreenWidth / num_2 * simon->GetTrend();
					
					if ((*it)->GetX() < Game_MapWidth - Game_ScreenWidth / num_2)
					{
						IsOpenTheGate = true;
						StepOpenTheGate = STEP_0;
					}
				}	
			}
		}

		//Check va cham voi enemy va mat mau
		if (CheckObject((*it)->GetType()) == IS_ACTION && simon->GetHurt() == NO_ACTION && simon->Invisible == NO_ACTION)
		{
			if ((Collide(simon->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny)) == IS_COLLIDE)
			{
					if (!(simon->GetOnStair())) simon->Hurt(simon->GetX() > (*it)->GetX());
					else simon->SetHurt(number_50);
					Sound->PlaySound(SimonHurt);
					simon->SetAlive(num_1);
			}
		}
	}
	//Khong con di tren gach va rot chet
	if (GoOnBrick == false)
	{
		if (!simon->GetFalling() && !simon->GetJumping() && !(simon->GetOnStair()))
		{
			simon->Jump(); 
			simon->Fall();
			simon->SimonFall = IS_ACTION;
		}
	}

	ListObj.clear();
	/////////////////////////////////////////////////////////////////////
	
	//Check va cham voi vu khi cua enemy.
	for (int i = number_0; i < EnemyWeapons.size(); i++)
	{
		Box BoxWp = EnemyWeapons.at(i)->GetBox(camera);
		if (simon->GetHurt() == NO_ACTION && EnemyWeapons.at(i)->GetFinish() == NO_ACTION && simon->Invisible == NO_ACTION)
		{
			if ((Collide(simon->GetBox(camera), BoxWp, CollideTime, nx, ny) == IS_COLLIDE))
			{
				if (!(simon->GetOnStair())) simon->Hurt(simon->GetX() > EnemyWeapons.at(i)->x);
				else simon->SetHurt(num_30);
				Sound->PlaySound(SimonHurt);

				simon->SetAlive(num_1);
				EnemyWeapons.at(i)->SetFinish();
			}
		}
	}

	//Kiem tra va cham voi enemy dang di chuyen PANTHER FISHMAN quay nguoc 
	for (int i = 0; i < Enemy.size(); i++)
	{
		
		if ((Enemy.at(i)->GetType() == PANTHER || Enemy.at(i)->GetType() == GHOUL) && Enemy.at(i)->GetMoving())
		{
			GoOnBrick = false;
			for (it = Ground.begin(); it != Ground.end(); it++)
			{
				if ((*it)->GetType() == BRICK)
				{
					int IsCollide = Collide(Enemy.at(i)->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
					if (IsCollide == COLLIDE_TOP || (IsCollide == IS_COLLIDE && (*it)->GetY() < Enemy.at(i)->GetY()))
					{
						float setY = (*it)->GetY() + (*it)->GetHeight() - 16 * (Enemy.at(i)->GetType() == PANTHER);
						if (IsCollide == COLLIDE_TOP)
						{
							//Quay nguoc lai khi X cua Enemy < X cua Simon;
							Enemy.at(i)->StopFall(setY);
							if (Enemy.at(i)->GetX() <= simon->GetX()) Enemy.at(i)->MoveRight();
						}
						GoOnBrick = true;
						Enemy.at(i)->StopFall(setY);
					}

					if ((IsCollide == COLLIDE_LEFT || IsCollide == COLLIDE_RIGHT) && Enemy.at(i)->GetType() == GHOUL)
					{
						Enemy.at(i)->SetAlive(1);
					}
				}
			}
			//Khong con tren gach thi nhay va rot
			if (GoOnBrick == false)
			{
				if (!Enemy.at(i)->GetFalling() && !Enemy.at(i)->GetJumping())
				{
					Enemy.at(i)->Jump(); 
					Enemy.at(i)->Fall();
				}
			}
		}
		else
			//Enemy la nguoi ca
			if (Enemy.at(i)->GetType() == FISH_MAN)
			{
				GoOnBrick = false;
				for (it = Ground.begin(); it != Ground.end(); it++)
				{
					
					if ((*it)->GetType() == BRICK)
					{
						int IsCollide = Collide(Enemy.at(i)->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
						if (IsCollide)
						{
							if (Enemy.at(i)->GetFalling() && IsCollide == COLLIDE_TOP)
							{
								Enemy.at(i)->StopFall(Enemy.at(i)->GetY() + Enemy.at(i)->GetVy()*CollideTime);
							}
							if (Enemy.at(i)->GetMoving() && (IsCollide == COLLIDE_LEFT || IsCollide == COLLIDE_RIGHT))
							{
								Enemy.at(i)->SetX(Enemy.at(i)->GetX() + Enemy.at(i)->GetVx()*CollideTime - Enemy.at(i)->GetWidth() / num_2);
								if (Enemy.at(i)->GetTrend() == RIGHT) Enemy.at(i)->MoveLeft();
								else Enemy.at(i)->MoveRight();
							}
							GoOnBrick = true;
						}
					}
				}
				if (GoOnBrick == false)
				{
					if (!Enemy.at(i)->GetFalling() && !Enemy.at(i)->GetJumping())
					{
						Enemy.at(i)->Jump(); 
						Enemy.at(i)->Fall();
					}
				}
			}
		//Nguoi ca rot xuong nuoc
		if (Enemy.at(i)->GetType() == FISH_MAN && Enemy.at(i)->Water == number_0)
		{
			for (it = Invisi.begin(); it != Invisi.end(); it++)
			{
				
				if ((*it)->GetType() == WATER_OBJECT)
				{
					int IsCollide = Collide(Enemy.at(i)->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
					if (IsCollide)
					{
						Effects.push_back(new Water(Enemy.at(i)->GetX(), (*it)->GetY()));
						Enemy.at(i)->Water = number_50;
						Sound->PlaySound(FallWater);
					}
				}
			}
		}

	}

	ListObj.clear();

	//Check mang Weapons co the va cham voi object va rot do
	for (int i = number_0; i < Weapons.size(); i++)
	{
		
		if (Weapons.at(i)->GetFinish() == NO_ACTION && Weapons.at(i)->GetType() < FIRE_BALL)
		{
			Object *WeaponObj = new CameraObject(Weapons.at(i)->x, Weapons.at(i)->y, Weapons.at(i)->Size->FrameWidth, Weapons.at(i)->Size->FrameHeight);
			
			QuadtreeCollide->ResetTake();
			//Khoi tao cac doi tuong Obj co the va cham voi Weapon
			QuadtreeCollide->Retrieve(ListObj, WeaponObj, number_0, camera, number_0);

			for (it = ListObj.begin(); it != ListObj.end(); it++)
			{
				int isCollide = Collide(Weapons.at(i)->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
				if (isCollide && (CheckObject((*it)->GetType()) > number_0))
				{
					if (!(*it)->GetHurt())
					{
						Sound->PlaySound(Hit);

						(*it)->SetAlive(1);

						if (Weapons.at(i)->GetType() > number_0) (*it)->SetAlive(IS_ACTION);        

						if (Weapons.at(i)->GetType() == MORNING_STAR && Weapons.at(i)->GetTypeMorningStar() > num_1) (*it)->SetAlive(IS_ACTION);

						if ((*it)->GetAlive() == NO_ACTION)
						{
							//Effect fire cho item khi rot ra
							Effects.push_back(new Fire((*it)->GetX(), (*it)->GetY()));
							//Sau khi Boxx chet nem lua va rot ball
							if ((*it)->GetType() == BOSS_BAT)
							{
								Effects.push_back(new Fire((*it)->GetX() - num_30, (*it)->GetY()));
								Effects.push_back(new Fire((*it)->GetX() + num_30, (*it)->GetY()));
								Effects.push_back(new Fire((*it)->GetX() - num_30, (*it)->GetY() - num_20));
								Effects.push_back(new Fire((*it)->GetX(), (*it)->GetY() - num_20));
								Effects.push_back(new Fire((*it)->GetX() + num_30, (*it)->GetY() - num_20));
								//Cho rot Ball khi giet chet boss
								Items.push_back(new BallItem(camera->viewport.x + Game_ScreenWidth / num_2, camera->viewport.y - Game_ScreenHeight / num_2));
							}
							//Danh vao enemy se rot item gi
							if ((*it)->GetType() != BOSS_BAT) Items.push_back(GetTypeItem((*it)->GetX(), (*it)->GetY(), (*it)->GetID()));
						}

						Effects.push_back(new Star((*it)->GetX() + num_2, (*it)->GetY()));
						
						if (Weapons.at(i)->GetType() == SWORD)
						{
							Weapons.at(i)->SetFinish();
							break;
						}
					}
				}
			}
			ListObj.clear();
		}

		//Quang boom va cham san` va ra lua~
		if (Weapons.at(i)->GetType() == BOTTLE)
		{
			//Box wp = Weapons.at(i)->GetBox(camera);
			for (int j = number_0; j < Ground.size(); j++)
			{
				int isCollide = Collide(Weapons.at(i)->GetBox(camera), Ground.at(j)->GetBox(camera), CollideTime, nx, ny);
				if (isCollide == COLLIDE_TOP)
				{
					Weapons.at(i)->y = Ground.at(j)->GetY() + Ground.at(j)->GetHeight() - num_4;
					Weapons.at(i)->Boom();
					Sound->PlaySound(HolyWater);
				}
			}
		}

		//Bumeran quay ve va cham voi simon va bien mat
		if (Weapons.at(i)->GetType() == BUMERAN)
		{
			int IsCollide = Collide(Weapons.at(i)->GetBox(camera), simon->GetBox(camera), CollideTime, nx, ny);
			if (IsCollide == IS_COLLIDE && Weapons.at(i)->BumeranColide)
			{
				Weapons.at(i)->SetFinish();
			}

			
		}
	}

	//Check va cham cua Simon voi Items
	for (int i = number_0; i < Items.size(); i++)
	{
		if (Items.at(i)->Collide()) 
		{
			
			if (Items.at(i)->GetFinish() == NO_ACTION && AABBCheck(simon->GetBox(camera), Items.at(i)->GetBox(camera)))
			{
				Items.at(i)->SetFinish();
				if (Items.at(i)->GetType() == MONEYBAG_ITEM)
				{
					SaveMoney = Items.at(i)->GetMoney();
					Items.push_back(new MoneyBagItem(SaveMoney, simon->GetX(), simon->GetY()));
				}
				CheckItem(d3ddv, Items.at(i)->GetType());
			}

			
			GoOnBrick = false;
			//Item rot cham ground
			for (it = Ground.begin(); it != Ground.end(); it++)
			{
				if ((*it)->GetType() == BRICK)
				{
					int IsCollide = Collide(Items.at(i)->GetBox(camera), (*it)->GetBox(camera), CollideTime, nx, ny);
					if (IsCollide == COLLIDE_TOP)
					{
						if (Items.at(i)->GetType() != 0) Items.at(i)->y = (*it)->GetY() + (*it)->GetHeight() - num_16;
						Items.at(i)->StopFall();
					}
				}
			}
		}
	}
	//Delete Quadtree
	delete(QuadtreeCollide);
}

void SceneMain::DrawObjects(LPDIRECT3DDEVICE9 d3ddv)
{
	//An trung chu thap va chop chop man hinh
	if (RuningHolyCross)
	{
		if (RuningHolyCross % num_4 != number_0) d3ddv->ColorFill(Game_BackBuffer, NULL, D3DCOLOR_XRGB(num_255, num_255, num_255));
		if (RuningHolyCross == num_20) RuningHolyCross = NO_ACTION;
		else RuningHolyCross++;
	}
	//Ve map 
	map->DrawMap(camera);
	
	if (State == -num_1) return;
	//Render cac Object THEO CAMERA
	for (int i = number_0; i < ObjectsRender.size(); i++)
	{
		if (ObjectsRender.at(i)->GetType() != TORCH)
		{
			if (ObjectsRender.at(i)->GetAlive()) ObjectsRender.at(i)->DrawObject(camera);
		}
	}

	if (SceneEnding == IS_ACTION && State == STEP_1) 
	{
		int w = simon->GetX() + simon->Size->FrameWidth > simon->Size->FrameWidth;//test ? test - simon->GetX() : simon->Size->FrameWidth;
		D3DXVECTOR2 pos = camera->Transform(simon->GetX(), simon->GetY());
		simon->ObjectSprite->DrawApart(pos.x, pos.y, w);
	}
	else
	{
		int t = rand() % num_255;
		if (CollectMorningStar) simon->ObjectSprite->SetARGB(num_255, rand() % num_255, t, t / num_2);
		simon->DrawObject(camera);
		if (CollectMorningStar) simon->ObjectSprite->SetARGB();
	}

	if (State == STEP_1)
	{
		for (int i = number_0; i < ObjectsRender.size(); i++)
			if (ObjectsRender.at(i)->GetType() == TORCH && ObjectsRender.at(i)->GetAlive())
				ObjectsRender.at(i)->DrawObject(camera);
	}
	//Ve vu khi
	for (int i = number_0; i < Weapons.size(); i++)
	{
		if (Weapons.at(i)->GetFinish() == NO_ACTION)
		{
			Weapons.at(i)->SetXY(simon->GetX(), simon->GetY());
			Weapons.at(i)->DrawWeapon(camera);
		}
	}
	//Ve dan ban cua enemy
	for (int i = number_0; i < EnemyWeapons.size(); i++)
	{
		if (EnemyWeapons.at(i)->GetFinish() == NO_ACTION)
		{
			EnemyWeapons.at(i)->SetXY(simon->GetX(), simon->GetY());
			EnemyWeapons.at(i)->DrawWeapon(camera);
		}
	}
	//Ve hieu ung 
	for (int i = number_0; i < Effects.size(); i++)
	{
		Effects.at(i)->Draw(camera);
	}
	//Ve item
	for (int i = number_0; i < Items.size(); i++)
	{
		Items.at(i)->DrawItem(camera);
	}
	//Ve map khi ket thuc 2 sTATE 1
	if (SceneEnding == IS_ACTION && State == STEP_1)
	{
		map->DrawMap2(d3ddv, camera);
	}

	if (StepOpenTheGate == STEP_2)
	{
		simon->DrawObject(camera);
	}
}

void SceneMain::LoadMainMenu()
{
	State = -num_1;
	map = new Map();
	CamObj = new CameraObject();

	Sound->LoopSound(Menu);
}

void SceneMain::Scene0()
{
	LevelTime = number_0;
	map = new Map();
	CamObj = new CameraObject();

	simon = new Simon(num_3, num_1, Game_ScreenWidth - num_20, num_80, -num_1);
	simon->ObjectSprite->_timeAni = number_50;
	SimonAfter = simon->GetX();

	camera = new GameCamera(simon->GetX(), simon->GetY());
	ObjectsRender.clear();
	ObjectsRender.push_back(new InvisibleObject(Game_ScreenWidth / num_2 - num_60, simon->GetY()));     
	ObjectsRender.push_back(new BatIntroGame());
	ObjectsRender.push_back(new CloudIntroGame());
	Sound->StopSound(Menu);
	Sound->PlaySound(GameStart);
}

void SceneMain::Scene1()
{
	LevelTime = number_0;
	Objects.clear();
	SceneEnding = NO_ACTION;

	map = new Map();
	CamObj = new CameraObject();
	
	Level = num_1;
	simon = new Simon(number_5, number_0, num_30, num_120, num_1);
	simon->Jump();
	simon->Fall();
	SimonAfter = simon->GetX();

	camera = new GameCamera(simon->GetX(), simon->GetY());

	ReadQuadTree("Resources/map/Obj_1.txt");

	QuadtreeRender->ReadQuadTree("Resources/map/QuadTree_1.txt");

	Sound->StopSound(GameStart);
	Sound->LoopSound(MusicState1);
}

int SceneMain::EndScene1()
{
	SceneEnding = IS_ACTION;
	simon->Go();
	simon->SetAnimation(num_2, number_0, num_70);
	if (simon->GetX() >= Game_MapWidth - num_100) return IS_ACTION;
	return NO_ACTION;
}

void SceneMain::Scene2()
{
	Win = NO_ACTION;
	BossAction = NO_ACTION;
	BossId = -num_1;
	EatBall = NO_ACTION;
	LevelTime = NO_ACTION;
	Objects.clear();
	SceneEnding = NO_ACTION;

	map = new Map();
	
	Level = num_1;
	Floor = num_2;
	simon = new Simon(number_5, number_0, num_40, num_445, num_1);
	SimonAfter = simon->GetX();
	camera = new GameCamera(simon->GetX(), simon->GetY(), number_0, num_3071);


	ReadQuadTree("Resources/map/Obj_2.txt");
	 
	QuadtreeRender->ReadQuadTree("Resources/map/QuadTree_2.txt");

	simon->UpdateResetPosition();
	SaveFloor = Floor;
	DVx = camera->viewport.x;
	DVy = camera->viewport.y;
	DMinVx = camera->_minSize;
	DMaxVx = camera->_maxSize;

	Sound->LoopSound(MusicState1);
}

//Check cac object sao khi readQuadtree
int CheckCreated(int a)
{
	if (a >= BAT && a <= WATER_OBJECT) return num_1;
	if (a == BOSS_BAT) return num_1;
	return number_0;
}

//Tra ve object tuong ung theo quadtree
Object * SceneMain::GetTypeObject(int type, float x, float y, float w, float h, int trend)
{
	if (type == BAT) return new Bat(x, y);
	if (type == GHOUL) return new Ghoul(x, y);
	if (type == PANTHER) return new Panther(x, y);
	if (type == FISH_MAN) return new FishMan(x, y);
	if (type == TORCH) return new Torch(x, y);
	if (type == CANDLE) return new Candle(x, y);
	if (type == BRICK) return new Brick(x, y, w, h);
	if (type == STAIR) return new Stair(x, y, trend);
	if (type == STAIR2) return new Stair2(x, y, trend);
	if (type == UP_STAIR_OBJECT) return new UpStairObject(x, y, trend);
	if (type == DOWN_STAIR_OBJECT) return new DownStairObject(x, y, trend);
	if (type == DOOR) return new Door(x, y);
	if (type == INVISIBLE_OBJECT) return new InvisibleObject(x, y);
	if (type == WATER_OBJECT) return new WaterObject(x, y);
	if (type == BOSS_BAT) return new BossBat(x, y);
}

//Ham ReaQuadTree de load cac object va khoi tao Cac Object
void SceneMain::ReadQuadTree(char * filename)
{
	int i, j;
	FILE *file;
	file = fopen(filename, "r");
	int id, type, trend;
	float x, y, w, h;
	while (num_1)
	{
		fscanf(file, "%d %d %d %f %f %f %f", &id, &type, &trend, &x, &y, &w, &h);
		if (id + type + trend + x + y + w + h == number_0) break;
		if (CheckCreated(type))
		{
			Objects.push_back(GetTypeObject(type, x, y, w, h, trend));
			Objects.back()->SetId(Objects.size());
			Objects.back()->SetTrend(trend);
			Objects.back()->BackupPosition();
		}
	}

	QuadtreeRender = new QuadTree(number_0, number_0, number_0, Game_MapWidth, Game_MapHeight, Objects);
	fclose(file);
}

//Ham kiem tra cac Object(Enemies) de ve cac object theo quadtree cung nhu xet va cham
int SceneMain::CheckObject(int Type) 
{
	//BAT = 0; GHOUL = 1; PANTHER = 2; FISH_MAN = 3;
	if (Type >= BAT && Type <= FISH_MAN) return num_1;
	if (Type == BOSS_BAT) return num_1;
	if (Type == TORCH || Type == CANDLE) return num_2;
	return number_0;
}
//Ham ve thanh mau, mang, srcore,......
void SceneMain::DrawBoard(LPDIRECT3DDEVICE9 d3ddv)
{
	if (BossId == -1) health->DrawObject(simon->GetAlive(), 20*(Win == 0));
	else health->DrawObject(simon->GetAlive(), Enemy.at(BossId)->GetAlive());

	blackboard->DrawObject(camera);
	Arial->Render((char*)FullNumber(Heart, 2).c_str(), Game_ScreenWidth / 2 + 175, 37);
	Arial->Render((char*)FullNumber(RevivalNumber, 2).c_str(), Game_ScreenWidth / 2 + 175, 55);
	weaponboard->DrawObject(Weapon2);
	shotboard->DrawObject(Shot);

	if (!IsPause && !EatBall) LevelTime++;

	int time = num_900 - LevelTime / num_30;

	if (Win == IS_ACTION)
	{
		if (time < num_20)
		{
			if (time % num_2 == number_0) Sound->PlaySound(TimeUp);
		}
		if (time == number_0)
		{
			if (State <= STEP_2) Sound->StopSound(MusicState1);
			ResetResource(d3ddv);
		}
	}
	
	Arial->Onlost();
	Arial->Render("SCORE--", 5, 5);
	Arial->Render((char*)FullNumber(Score, 10).c_str(), 90, 5);
	Arial->Render("TIME", 230, 5);
	Arial->Render((char*)FullNumber(time, 4).c_str(), 300, 5);
	Arial->Render("STAGE", 400, 5);
	Arial->Render((char*)FullNumber(Level, 2).c_str(), 480, 5);
	Arial->Render("PLAYER", 5, 27);
	Arial->Render("ENEMY", 5, 50);
	Arial->Render("X: ", 5, 70);
	Arial->Render((char*)FullNumber(simon->GetX(), 5).c_str(), 30, 70);
	Arial->Render("Y: ", 90, 70);
	Arial->Render((char*)FullNumber(simon->GetY(), 5).c_str(), 120, 70);
	//Arial->Render((char*)FullNumber(CollectMorningStar,4).c_str(), 235, 70); //XToOpen
	//Arial->Render((char*)FullNumber(Floor, 1).c_str(), 300, 70); //OpeningTheGate
	//Arial->Render((char*)FullNumber(OpeningTheGate, 3).c_str(), 235, 70);
	if (TestGame)
	{
		if (simon->GetJumping())
		{
			if (tt < simon->GetY()) tt = simon->GetY();
		}
		if (BossAction && BossId != -1)
		{
			//Arial->Render((char*)FullNumber(Enemy.at(BossId)->Vx, 3).c_str(), 235, 70);
		}
	}
}
//Ham tinh diem sau khi an ball
void SceneMain::CalculatorScore()
{
	//Clear het object xong bat dau tinh diem
	if (WaitingTime_ScenceClear <= num_140)
	{
		WaitingTime_ScenceClear++;
		if (WaitingTime_ScenceClear % num_2 != number_0 && simon->GetAlive() < num_20) simon->SetAlive(-num_1);
	}
	else
	{
		Calculating++;
		int time = num_900 - LevelTime / num_30;
		if (time > number_0)
		{
			Score = Score + num_10;
			LevelTime += num_30;
			Sound->LoopSound(CalScore1);
		}
		else
		{
			Sound->StopSound(CalScore1);
			if (Heart > number_0)
			{
				Score = Score + num_100;
				Heart--;
				Sound->LoopSound(CalScore2);
			}
		}

		if (Heart == number_0 && time == number_0)
		{
			Calculating = NO_ACTION;
			Sound->StopSound(CalScore2);
		}
	}
}
//Ham mo cua
void SceneMain::OpenTheGate()
{
	//1 VA CHAM CUA, 2 QUA CUA, 3 KET THUC
	if (StepOpenTheGate == STEP_0)
	{
		simon->BonusVx = NO_ACTION;

		Enemy.clear();

		camera->viewport.x += num_4 * simon->GetTrend();

		if ((camera->viewport.x >= XToOpen && simon->GetTrend() > number_0) || (camera->viewport.x <= XToOpen && simon->GetTrend() < number_0))
		{
			StepOpenTheGate++;
			OpeningTheGate = STEP_1;
			Sound->PlaySound(OpenDoor);
		}
		return;

	}
	if (StepOpenTheGate == STEP_1)
	{
		if (OpeningTheGate == STEP_2) StepOpenTheGate++;
		return;
	}
	if (StepOpenTheGate == STEP_2)
	{
		simon->Go();

		if ((simon->GetX() >= camera->viewport.x + (Game_ScreenWidth / num_2) + num_70 && simon->GetTrend() > number_0)
			|| (simon->GetX() <= camera->viewport.x + (Game_ScreenWidth / num_2) - num_70 && simon->GetTrend() < number_0))
		{
			OpeningTheGate = STEP_0;
			StepOpenTheGate++;
			simon->Stop();
			simon->UpdateResetPosition();
			Level++;
			Sound->PlaySound(OpenDoor);
		}
		return;
	}
	if (StepOpenTheGate == STEP_3)
	{
		camera->viewport.x += num_4 * simon->GetTrend();

		if ((camera->viewport.x >= XToOpen + Game_ScreenWidth / num_2 && simon->GetTrend() > number_0)
			|| (camera->viewport.x <= XToOpen - Game_ScreenWidth / num_2 && simon->GetTrend() < number_0))
		{
			StepOpenTheGate = STEP_0;
			IsOpenTheGate = NO_ACTION;
			if (State == STEP_2)
			{
				//4098 vi tri X moi cua Simon
				if (camera->viewport.x < STATE_2_X1 + Game_ScreenWidth / num_2) camera->SetSizeMap(camera->viewport.x, num_4098);
				//Cua 2,
				else if (camera->viewport.x < STATE_2_X2 + Game_ScreenWidth / num_2) camera->SetSizeMap(camera->viewport.x, Game_MapWidth);
			}
			SaveFloor = Floor;
			DVx = camera->viewport.x;
			DVy = camera->viewport.y;
			DMinVx = camera->_minSize;
			DMaxVx = camera->_maxSize;
		}
		return;
	}
}
//Ham di xuong cau thang
void SceneMain::GoDownStair(float x, float y, int trend)
{
	if (StepDownStair == STEP_0) 
	{
		simon->AutoGo = IS_ACTION;
		if (trend == LEFT)  
		{
			if (x < simon->GetX()) simon->MoveLeft(); 
			else simon->MoveRight();
		}
		else  
		{
			if (simon->GetX() < x) simon->MoveRight();
			else  simon->MoveLeft();
		}

		simon->SetAnimation(number_5, number_0, number_50); 
		StepDownStair = STEP_1;
		return;
	}

	if (StepDownStair == STEP_1)
	{
		simon->Go();
		if (trend == LEFT && simon->GetTrend() == LEFT && simon->GetX() < x)
		{
			StepDownStair = STEP_0;
			return;
		}

		if (trend == LEFT && simon->GetX() <= x && simon->GetX() + simon->GetVx() > x)
		{
			simon->MoveRight();
			simon->SetX(x + number_5);
			simon->Stop();
			simon->DownStair();
			StepDownStair = STEP_2;
			return;
		}

		if (trend == RIGHT && simon->GetTrend() == RIGHT && simon->GetX() > x)
		{
			StepDownStair = STEP_0;
			return;
		}
		if (trend == RIGHT && simon->GetX() >= x && simon->GetX() + simon->GetVx() < x)
		{
			simon->MoveLeft();
			simon->SetX(x + number_5);
			simon->Stop();
			simon->DownStair();
			StepDownStair = STEP_2;
			return;
		}
	}

	if (StepDownStair == STEP_2)
	{
		simon->Go();
		StepDownStair = STEP_3;
	}

	if (StepDownStair == STEP_3)
	{
		if (simon->AutoGo == NO_ACTION)
		{
			DownStairPre = NO_ACTION;
			simon->Stop();
		}
	}
}
//Ham di tren cau thang
void SceneMain::GoUpStair(float x, float y, int trend)
{
	//Cham cau thang va tu dong thuc hien animation de len cau thang
	if (StepUpStair == STEP_0) 
	{
		simon->AutoGo = IS_ACTION;
		if (trend == LEFT) 
		{
			if (x < simon->GetX()) simon->MoveLeft(); 
			else simon->MoveRight();
		}
		else 
		{
			if (simon->GetX() < x) simon->MoveRight();
			else  simon->MoveLeft();
		}

		simon->SetAnimation(number_5, number_0, number_50);
		StepUpStair = STEP_1;
		return;
	}
	//Sau khi xong Animation
	if (StepUpStair == STEP_1)
	{
		simon->Go();
		if (trend == LEFT && simon->GetTrend() == LEFT && simon->GetX() < x)
		{
			StepUpStair = STEP_0;
			return;
		}

		if (trend == LEFT && simon->GetX() <= x + number_5 && simon->GetX() + simon->GetVx() >= x)
		{
			simon->MoveRight();
			simon->SetX(x + number_5);
			simon->Stop();
			simon->UpStair();
			StepUpStair = STEP_2;
			return;
		}

		if (trend == RIGHT && simon->GetTrend() == RIGHT && simon->GetX() > x)
		{
			StepUpStair = STEP_0;
			return;
		}

		if (trend == RIGHT && simon->GetX() >= x - number_5 && simon->GetX() + simon->GetVx() < x)
		{
			simon->MoveLeft();
			simon->SetX(x + number_5);
			simon->Stop();
			simon->UpStair();
			StepUpStair = STEP_2;
			return;
		}
	}

	if (StepUpStair == STEP_2)
	{
		simon->Go();
		StepUpStair = STEP_3;
	}
	//Da o tren cau thang
	if (StepUpStair == STEP_3)
	{
		if (simon->AutoGo == NO_ACTION)
		{
			UpStairPre = NO_ACTION;
			simon->Stop();
		}
	}
}
//Ham kiem tra cac item khi simon nhat duoc
void SceneMain::CheckItem(LPDIRECT3DDEVICE9 d3ddv, int type)
{
	if (type == POINT_MONEYBAT_ITEM) return;

	if (type >= MORNINGSTAR_ITEM && type <= BOTTLE_ITEM && type != CROSS_ITEM)
	{
		if (type == MORNINGSTAR_ITEM)
		{
			Weapons.at(number_0)->SetTypeMorningStar();
			CollectMorningStar = num_1;
		}
		if (type == SWORD_ITEM) Weapon2 = SWORD;
		if (type == BOTTLE_ITEM) Weapon2 = BOTTLE;
		if (type == AXE_ITEM) Weapon2 = AXE;
		if (type == BUMERAN_ITEM) Weapon2 = BUMERAN;
		if (type == STOPWATCH_ITEM) Weapon2 = STOPWATCH_ITEM;
		Sound->PlaySound(CollectWeapon);
		return;
	}
	if (type <= MONEYBAG_ITEM)
	{
		if (type == HEART_ITEM) Heart += num_1;
		if (type == BIGHEART_ITEM) Heart += number_5;

		if (type == MONEYBAG_ITEM) Score += SaveMoney;
		Sound->PlaySound(CollectItem);
		return;
	}

	if (type >= PORKCHOP_ITEM && type <= POTION_ITEM)
	{
		if (type == SHOT2_ITEM) Shot = num_2;
		if (type == SHOT3_ITEM) Shot = num_3;

		if (type == PORKCHOP_ITEM) simon->SetAlive(-num_6);

		if (type == BALL_ITEM)
		{
			EatBall = IS_ACTION;
			Sound->StopSound(BossBattle);
			Sound->StopSound(MusicState1);
			Sound->PlaySound(ScenceClear);
			WaitingTime_ScenceClear = NO_ACTION;
			Calculating = NO_ACTION;
			CalculatorScore();
		}

		if (type == POTION_ITEM)
		{
			simon->Invisible = IS_ACTION;
			Simon_Invisi_Time = IS_ACTION;
			Sound->PlaySound(Potion);
		}

		if (type != POTION_ITEM) Sound->PlaySound(CollectItem);
		return;
	}

	if (type == CROSS_ITEM)
	{
		Sound->PlaySound(HolyCross);
		RuningHolyCross = IS_ACTION;
		for (int i = number_0; i < Enemy.size(); i++)
		{
			if (Enemy.at(i)->GetType() != BOSS_BAT)
			{
				D3DXVECTOR2 pos = camera->Transform(Enemy.at(i)->GetX(), Enemy.at(i)->GetY());
				if (pos.x >= number_0 && pos.x <= Game_ScreenWidth && pos.y >= number_0 && pos.y <= Game_ScreenHeight)
				{
					Enemy.at(i)->SetAlive(num_100);
					Effects.push_back(new Fire(Enemy.at(i)->GetX(), Enemy.at(i)->GetY()));
				}
			}
		}
	}
}

//Check object se rot mon do gi!
Item * SceneMain::GetTypeItem(float x, float y, int id)
{
	//Cheat game cho item ke tiep se rot mon gi
	if (NextItem == CROSS_ITEM) { return new CrossItem(x, y); }
	if (NextItem == POTION_ITEM) { NextItem = -1; return new Potion_Item(x, y); }
	if (NextItem == STOPWATCH_ITEM) { NextItem = -1; return new StopwatchItem(x, y); }

	if (State == STEP_1)
	{
		if (id == 1 || id == 2 || id == 5) return new BigheartItem(x, y);
		if (id == 3 || id == 4) return new MorningStarItem(x, y);
		if (id == 6) return new SwordItem(x, y);
	}

	if (State == STEP_2)
	{
		if (id == 117 || id == 127 || id == 129 || id == 135 || id == 140) return new BigheartItem(x, y);
		if (id == 98 || id == 108 || id == 109 || id == 121 || id == 122 || id == 124) return new MoneyBagItem(x, y);
		if (id == 106) return new BottleItem(x, y);
		if (id == 116 || id == 131) return new CrossItem(x, y);
		if (id == 120) return new PorkChopItem(x, y);
		if (id == 125) return new StopwatchItem(x, y);
		if (id == 134) return new Potion_Item(x, y);
		if (id == 138) return new AxeItem(x, y);
		if (id == 142)
		{
			if(Shot == 1) return new II_Item(x, y);
			if (Shot == 2) return new III_Item(x, y);
			else
				return new HeartItem(x, y);
		}
	}

	if (Weapons.at(0)->GetTypeMorningStar() < 3)
		return new MorningStarItem(x, y);
	else
		return new HeartItem(x, y);
}

void SceneMain::MoveCamera(bool left, bool right, bool up, bool down)
{
	if (State == STEP_2)
	{
		if (right || down)
		{
			if (simon->GetX() < 3300 && simon->GetY() < 415 && Floor == 2)
			{
				simon->SetX(3227);//NEW X Down simon cau thang 1
				simon->SetY(325);//NEW Y Down simon cau thang 1
				MoveDownCamera();
				return;
			}
			if (simon->GetX() > 3700 && simon->GetY() < 415 && Floor == 2)
			{
				simon->SetX(3852);//NEW X Down simon cau thang 2
				simon->SetY(332);//NEW X Down simon cau thang 2
				MoveDownCamera();
				return;
			}
			return;
		}

		if (left || up)
		{
			if (simon->GetX() < 3200 && simon->GetY() > 350 && Floor == 1)
			{
				simon->SetX(3182);//NEW X UP simon cau thang 1
				simon->SetY(431);//NEW Y UP simon cau thang 1
				MoveUpCamera();
				return;
			}
			if (simon->GetX() > 3700 && simon->GetY() > 350 && Floor == 1)
			{
				simon->SetX(3820);//NEW X UP simon cau thang 2
				simon->SetY(430);//NEW X UP simon cau thang 2
				MoveUpCamera();
				return;
			}
		}
	}
}

void SceneMain::MoveDownCamera()
{
	Floor--;
	camera->viewport.y = Game_ScreenHeight + SIZE_384 * (Floor - 1);
}

void SceneMain::MoveUpCamera()
{
	camera->viewport.y = Game_ScreenHeight + SIZE_384 * Floor;
	Floor++;
}





