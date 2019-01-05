#include "GameCamera.h"

GameCamera::GameCamera(float x, float y, int minSize, int maxSize)
{
	float vx;
	if (x - Game_ScreenWidth / 2 <= minSize) vx = minSize;
	else
		if (x + Game_ScreenWidth / 2 >= maxSize ) vx = maxSize - Game_ScreenWidth;
		else
			vx = x - Game_ScreenWidth / 2;

	_minSize = minSize;
	_maxSize = maxSize;

	switch (State)
	{
		case 0:
		{
			viewport.x = minSize;
			viewport.y = Game_ScreenHeight;
			break;
		}
		case 1:
		{
			viewport.x = vx;
			viewport.y = Game_ScreenHeight;
			break;
		}
		case 2:
		{
			viewport.x = vx;
			viewport.y = Game_ScreenHeight + 384;
			break;
		}
	}
}

void GameCamera::SetSizeMap(int _min, int _max)
{
	_maxSize = _max;
	_minSize = _min;
}

int GameCamera::GetMaxSize()
{
	return _maxSize;
}

int GameCamera::GetMinSize()
{
	return _minSize;
}


D3DXVECTOR2 GameCamera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}

D3DXVECTOR3 GameCamera::CenterSprite(int x, int y)
{
	D3DXVECTOR3 pCenter = D3DXVECTOR3(x / 2, y / 2, 0);
	return pCenter;
}

void GameCamera::UpdateCamera(int x)
{
}

void GameCamera::UpdateCamera()
{
	
	if ((_FolowPosX >= Game_ScreenWidth / 2 + viewport.x && _VCameraX>0) || (_FolowPosX <= viewport.x + Game_ScreenWidth / 2 && _VCameraX<0))
	{
		viewport.x += _VCameraX;
	}
	
	if (viewport.x + Game_ScreenWidth > _maxSize) viewport.x = _maxSize - Game_ScreenWidth;
	if (viewport.x < _minSize) viewport.x = _minSize;
}

void GameCamera::SetVCam(float vcamX,float vcamY)
{
	

	_VCameraX = vcamX;
}

void GameCamera::SetFolowPos(float x, float y)
{
	_FolowPosX = x;
	_FolowPosY = y;
}



