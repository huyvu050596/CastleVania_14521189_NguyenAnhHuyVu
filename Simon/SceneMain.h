#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include <vector>
#include "Game.h"
#include "GameSprite.h"
#include "Object.h"
#include "Simon.h"
#include "Map.h"
#include "GameCamera.h"
#include "Bat.h"
#include "PhantomBat.h"
#include "FishMan.h"
#include "Panther.h"
#include "Ghoul.h"
#include "MorningStar.h"
#include "Weapon.h"
#include "BatIntroGame.h"
#include "CloudIntroGame.h"
#include "Torch.h"
#include "Candle.h"
#include "Brick.h"
#include "Stair.h"
#include "Stair2.h"
#include "UpStairObject.h"
#include "DownStairObject.h"
#include "WaterObject.h"
#include "Door.h"
#include "InvisibleObject.h"
#include "Swept_AABB.h"
#include "QuadTree.h"
#include "CameraObject.h"
#include "GameFont.h"
#include "PauseMenu.h"
#include "BoardPause.h"
#include "BlackBoard.h"
#include "Health.h"
#include "ShotBoard.h"
#include "Effect.h"
#include "Fire.h"
#include "Water.h"
#include "Star.h"
#include "Sword.h"
#include "Axe.h"
#include "Bumeran.h"
#include "Bottle.h"
#include "FireBall.h"
#include "WeaponBoard.h"
#include "Item.h"
#include "AxeItem.h"
#include "BottleItem.h"
#include "SwordItem.h"
#include "BumeranItem.h"
#include "MorningStarItem.h"
#include "BallItem.h"
#include "BigheartItem.h"
#include "HeartItem.h"
#include "CrossItem.h"
#include "II_Item.h"
#include "III_Item.h"
#include "MoneyBagItem.h"
#include "PorkChopItem.h"
#include "BossBat.h"
#include "GameAudio.h"
#include "Potion_Item.h"
#include "StopwatchItem.h"
#include "Global.h"
#include <iostream>
#include <string>
using namespace std;
class SceneMain : public CGame
{
	int tt = 0;
	
public:

	GameCamera *camera;
	Map *map;
	Simon *simon;
	CameraObject *CamObj;
	QuadTree* QuadtreeRender;
	QuadTree* QuadtreeCollide;
	vector<Object*> ObjectsRender;
	vector<Object*> Objects;

	vector<Object*> Enemy; 
	vector<Object*> Ground;
	vector<Object*> Invisi; 

	vector<Weapon*> Weapons;
	vector<Weapon*> EnemyWeapons;

	vector<Effect*> Effects;
	vector<Item*> Items;

	SceneMain(int _nCmdShow);

	int SceneEnding;
	bool GoOnBrick;

	int StepOpenTheGate;
	int XToOpen;

	int SaveFloor;
	float DVx;
	float DVy;
	float DMinVx;
	float DMaxVx;

	int IsWait;

	int UpStairPre;
	int StepUpStair;
	int DownStairPre;
	int StepDownStair;

	int GoUp;
	int GoDown;
	int Step;
	

	int Weapon2;

	RECT rect;

	int Simon_Invisi_Time = 0;
	int Stopwatch_Time = 0;
	int test = 0;
	int IsPause;
	int Level;
	int CurrentSelectPausedMenu;
	int LevelTime;
	int CollectMorningStar;
	char * ListPause[3];

	GameFont *Arial;
	GameFont *ArialBigger;
	BoardPause *blackboardpause;
	PauseMenu *pausemenu;
	BlackBoard *blackboard;
	WeaponBoard *weaponboard;
	ShotBoard *shotboard;
	Health *health;

	int Heart = 0;
	int RevivalNumber = 3;
	int WaitingTime;
	int Shot = 1;
	int Score = 0;
	int SaveMoney = 0;

	int BossAction = 0;
	int BossId;
	int EatBall = 0;

	int SimonBefore;
	int SimonAfter;

	int Win = 0;
	int MedusaAction_Time = 0;
	GameAudio *Sound;
	GSound *MusicState1;
	GSound *MusicState2;
	GSound *BossBattle;
	GSound *GameStart;
	GSound *SimonDie;
	GSound *Menu;

	GSound *CollectItem;
	GSound *CollectWeapon;
	GSound *Fall;
	GSound *FallWater;
	GSound *Hit;
	GSound *OpenDoor;
	GSound *Whip;
	GSound *CalScore1;
	GSound *CalScore2; 
	GSound *ScenceClear;
	GSound *HolyCross;
	GSound *HolyWater;
	GSound *Potion;
	GSound *WatchWeapon;
	GSound *SimonHurt;
	GSound *TimeUp;
	GSound *BoneTowerHurt;
	GSound *EndScence1;

	int RuningHolyCross;
	int NextItem;
	int Calculating;
	int WaitingTime_ScenceClear;

protected:
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void UpdateObjects(int t);
	void DrawObjects(LPDIRECT3DDEVICE9 d3ddv);
	void LoadMainMenu();
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ResetResource(LPDIRECT3DDEVICE9 d3ddv);
	//virtual void OnKeyDown(int KeyCode);

	void DrawBoard(LPDIRECT3DDEVICE9 d3ddv);
	void OpenTheGate();

	void GoUpStair(float x, float y, int trend);
	void GoDownStair(float x, float y, int trend);

	void MoveDownCamera();
	void MoveUpCamera();
	void CheckItem(LPDIRECT3DDEVICE9 d3ddv,int t);
	Item* GetTypeItem(float x, float y,int id);


	void Scene0();
	void Scene1();
	int EndScene1();
	void Scene2();
	void Scene3();
	void ReadQuadTree(char * filename, int New);
	Object* GetTypeObject(int type, float x, float y, float w, float h, int trend, int New);
	void ReadQuadTree(char * filename);
	Object* GetTypeObject(int type, float x, float y, float w, float h, int trend);
	void WriteQuadTree(char * filename);
	void DetectCollision(LPDIRECT3DDEVICE9 d3ddv, int t);
	int CheckObject(int Type);

	void MoveCamera(bool left, bool right, bool up, bool down);

	void CalculatorScore();
};

#endif