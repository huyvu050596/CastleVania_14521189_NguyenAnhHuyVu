#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define IMAGE_FILE "Resources/paused.png"

class PauseMenu :public Object
{
public:
	PauseMenu();
	~PauseMenu();
	void virtual DrawObject(GameCamera *camera);
};
#endif

