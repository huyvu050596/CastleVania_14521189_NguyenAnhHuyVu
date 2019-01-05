#ifndef _ITEM_H_
#define _ITEM_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "GameCamera.h"
#include "Global.h"

#define WAITINGTIME 300
#define VISIBLETIME 800

class Item
{
protected:
	GameTexture* Size;

	int IsFinish;
	int TypeItem;
	int IsStopFall;
	int WaitingTime;

	int VisibleTime;

public:
	float x;	     
	float y;	      
	float Vx;	     
	float Vy;	     
	Item();
	~Item();							   

	GameSprite* ItemSprite;

	virtual void Update(GameCamera *camera, int t);
	virtual Box GetBox(GameCamera *camera);
	virtual void DrawItem(GameCamera *camera);

	virtual int GetFinish();
	virtual void SetFinish();
	
	int GetType();
	void StopFall();
	int Collide();

	virtual int GetMoney();
};

#endif
