#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "GameCamera.h"
#include "Global.h"

class Weapon
{
protected:
	float simon_x, simon_y;
	float Vx;	     
	float Vy;	     

	float Speed;   

	int Trend;		        
	int DefaultTrend;

	int IsFinish;
	int WeaponType;

public:
	float x;	     
	float y;	      
	Weapon();
	~Weapon();							   

	GameSprite* WeaponSprite;
	GameTexture* Size;

	int GetTrend();
	void SetTrend(int a);

	virtual void Create(float sm_x, float sm_y, int sm_trend);
	virtual void Update(GameCamera *camera, int t);
	virtual Box GetBox(GameCamera *camera);
	virtual void DrawWeapon(GameCamera *camera);
	virtual void SetXY(float x, float y);

	virtual void SetTypeMorningStar(int i = -1);
	virtual int GetTypeMorningStar();

	virtual int GetFinish();
	virtual void SetFinish();

	int GetType();

	virtual void Boom();

	int BumeranColide;

	int IsFalling;     

	virtual void BumeranBack();        
};

#endif
