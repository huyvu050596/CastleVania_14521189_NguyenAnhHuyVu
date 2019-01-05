#ifndef CSPRITE_H
#define CSPRITE_H

#include <d3d9.h>
#include <d3dx9.h>

#include "GameTexture.h"

class GameSprite {
public:
	GameTexture* _texture;

	int _start;		
	int _end;		
	int _index;		
	int _timeAni;	
	int _timeLocal;

	GameSprite();
	GameSprite(const GameSprite &sprite);
	GameSprite(GameTexture* texture, int timeAnimation);
	GameSprite(GameTexture* texture, int start, int end, int timeAnimation);

	
	void Next();

	
	void Reset();

	
	void SelectIndex(int index);

	
	void Update(int ellapseTime);

	
	void Draw(int x, int y);

	
	void DrawFlipX(int x, int y);

	
	void DrawFlipY(int x, int y);

	
	void DrawRect(int X, int Y, RECT SrcRect);

	void DrawIndex(int index, int X, int Y);

	void DrawRaw(int X, int Y);
	int GetIndex();

	void DrawApart(int x, int y, int w);
	~GameSprite();

	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};

#endif