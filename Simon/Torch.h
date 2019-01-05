#ifndef _TORCH_H_
#define _TORCH_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"
#include "Global.h"

#define TORCH_IMAGE "Resources/ground/0.png"
#define TORCH_FRAME 100

class Torch:public Object
{
public:
	Torch(float, float, int fit = 1);
	~Torch();

	virtual void Update(GameCamera *camera, int t);
};
#endif
