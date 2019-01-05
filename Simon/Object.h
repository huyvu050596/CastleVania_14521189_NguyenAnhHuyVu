#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "Global.h"

class Object
{
protected:
	int id;
	float x;	     
	float y;	     

	int IsGoing;		         
	int IsAttacking;
	int IsStopping;
	int IsJumping;
	int IsSitting;
	int IsFalling;
	int DefaultTrend;
	int Trend;		        
	int PreAtk;
	int IsHurting;
	int EndHurt;

	int IsDraw;

	Weapon* weapon;
	int Type;   

	int DTrend;
	float Dx;
	float Dy;
	
public:
	GameTexture* Size;
	GameSprite* ObjectSprite;

	float Vx;	     
	float Vy;	     

	int Water;
	Object();
	~Object();	   

	int GetID();
	float GetX();
	float GetY();
	virtual float GetWidth();
	virtual float GetHeight();

	void SetX(float);
	void SetY(float);

	float GetVx();
	float GetVy();

	int GetMoving();
	void SetMoving(int a);

	int GetAttacking();

	int GetTrend();
	void SetTrend(int a);
	int GetFalling();
	int GetJumping();
	int GetType();
	int GetAlive();
	void SetAlive(int t);

	void SetId(int a);
	virtual Box GetBox(GameCamera *camera,int i = 1);
	virtual void ResetObj();
	virtual void Stop();
	virtual void Sit();
	virtual void StandUp();
	virtual void Fall();
	virtual void StopFall(float y);
	virtual void Jump();
	virtual void Go();
	virtual void Attack(Weapon *weapon = NULL);
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Update(GameCamera *camera, int t);
	virtual void DrawObject(GameCamera *camera);

	void FitPosision();
	void Hurting();
	void SetAnimation(float Vx, float Vy, int Frame);

	int GetHurt();
	void SetHurt(int i = 30);

	virtual int CreateWeapon(); 
	virtual void SetCreateWeapon();
	virtual void GetSMPositionForBoss(float x, float y,int Trend);

	virtual void ResetPosition();
	virtual void BackupPosition();
	int Health;
	int DHealth;

};

#endif
