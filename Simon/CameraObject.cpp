#include "CameraObject.h"


CameraObject::CameraObject()
{
}

CameraObject::CameraObject(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


CameraObject::~CameraObject()
{
}

void CameraObject::SetCameraObj(float x, float y, float w, float h)
{
	this->x = x + w / 2;
	this->y = y - h / 2;
	this->w = w;
	this->h = h;
}

float CameraObject::GetWidth()
{
	return w;
}

float CameraObject::GetHeight()
{
	return h;
}
