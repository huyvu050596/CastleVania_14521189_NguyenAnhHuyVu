#ifndef GFONT_H
#define GFONT_H

#include <d3dx9.h>
#include <iostream>
#include "Game.h"
#include "Global.h"
#include "GameCamera.h"

using namespace std;

class GameFont
{
private:
	LPD3DXFONT	_Font;
	RECT		_FontPosition;

	float x, y;
	int Number;
	int IsFinish;

public:
	GameFont(int size = 22);
	GameFont(int a, float x, float y);
	~GameFont();
	void Initialize(int size = 22);
	void Render(char* text, float x, float y, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Render(GameCamera *camera);
	int GetFinish();
	void Onlost();
};
#endif