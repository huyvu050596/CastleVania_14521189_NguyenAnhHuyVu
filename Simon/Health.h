#ifndef _HEALTH_H_
#define _HEALTH_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define IMAGE_FILE "Resources/health.png"
#define MAX_HEALTH 20

class Health :public Object
{
	int Simon = 0;
	int Boss = 2;
	int Empty = 1;
	int y[3];
public:
	Health();
	~Health();
	void virtual DrawObject(int HealthSimon = 20, int HealthBoss = 20);
};
#endif

