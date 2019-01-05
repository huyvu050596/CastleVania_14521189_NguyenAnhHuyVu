#ifndef _BLACKBOARDPAUSE_H_
#define _BLACKBOARDPAUSE_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define IMAGE_FILE "Resources/blackboardpause.png"

class BoardPause :public Object
{
public:
	BoardPause();
	~BoardPause();
	void virtual DrawObject(GameCamera *camera);
};
#endif

