#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global.h"
#include "GameSprite.h"

class GameCamera
{
public:
	D3DXVECTOR2 viewport;		
	int _maxSize, _minSize;
	float _VCameraX, _VCameraY;
	float _FolowPosX;
	float _FolowPosY;
	GameCamera(float x,float y, int minSize = 0, int maxSize = Game_MapWidth);
	D3DXVECTOR3 CenterSprite(int x, int y);	
	void UpdateCamera(int x);
	void UpdateCamera();
	void SetSizeMap(int _min, int _max);
	int GetMaxSize();
	int GetMinSize();
	void SetVCam(float vcamX,float vcamY);
	void SetFolowPos(float x, float y);
	D3DXVECTOR2 Transform(int x, int y);		

	void ResetCamera();
};

#endif