#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define IMAGE_FILE "Resources/blackboard.png"

class BlackBoard :public Object
{
public:
	BlackBoard();
	~BlackBoard();
	void virtual DrawObject(GameCamera *camera);
};
#endif

