#ifndef _CAMERAOBJ_H_
#define _CAMERAOBJ_H_

#include <d3dx9.h>
#include "GameSprite.h"
#include "Object.h"

class CameraObject : public Object
{
	float w, h;
public:
	CameraObject();
	CameraObject(float x, float y, float w, float h);
	~CameraObject();
	void SetCameraObj(float x, float y, float w, float h);
	virtual float GetWidth();
	virtual float GetHeight();
};
#endif
