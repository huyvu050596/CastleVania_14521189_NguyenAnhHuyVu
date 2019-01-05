#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class GameTexture 
{
public:
	char* FileName; 
	RECT Size;		
	LPDIRECT3DTEXTURE9 Texture;
	int Cols;		
	int Rows;		
	int Count;		
	int FrameWidth;		
	int FrameHeight;	

	GameTexture(char* _fileName, int cols = 1, int rows = 1, int count = 1, int Showbox = 0);
	GameTexture(char* _fileName, int cols, int rows, int count, int R, int G, int B);
	~GameTexture();
	
	void Draw(int x, int y);

protected:
	void Load(int ShowBox);
	void Load(int R, int G, int B);
};

#endif