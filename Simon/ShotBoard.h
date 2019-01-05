#ifndef _SHOTBOARd_H_
#define _SHOTBOARd_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

class ShotBoard :public Object
{
	GameSprite *ObjectSprite[4];

public:
	ShotBoard();
	~ShotBoard();
	void DrawObject(int t);
};
#endif

