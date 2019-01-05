#ifndef _CLOUD_INTRO_H_
#define _CLOUD_INTRO_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

#define CLOUD_IMAGE "Resources/helicopter.png"
#define CLOUD_FRAME 100

class CloudIntroGame : public Object
{
public:
	CloudIntroGame();
	~CloudIntroGame();

	virtual void Update(GameCamera *camera, int t);
};
#endif
