#ifndef _BAT_INTRO_H_
#define _BAT_INTRO_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define BAT_IMAGE "Resources/bat.png"
#define BAT_FRAME 100
#define BAT_X 50
#define BAT_Y 300

class BatIntroGame : public Object
{
public:
	BatIntroGame();
	~BatIntroGame();

	virtual void Update(GameCamera *camera, int t);
};
#endif
