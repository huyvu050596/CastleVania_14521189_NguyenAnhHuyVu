#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "GameCamera.h"

class Effect
{
protected:
	float x;	     
	float y;	     

	float Vx;	     
	float Vy;	     

	float Speed;   

	GameTexture* Size;
	GameSprite* EffectSprite;

	int FinishEffect;
public:
	Effect();
	~Effect();							   

	virtual void Update(GameCamera *camera, int t);
	virtual void Draw(GameCamera *camera);
	int GetFinish();
};

#endif
