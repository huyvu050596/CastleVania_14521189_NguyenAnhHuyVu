#include "GameFont.h"
#include "Game.h"
#include <string>
using namespace std;

GameFont::GameFont(int size)
{
	_Font = NULL;
	Initialize(size);
}

GameFont::GameFont(int a, float x, float y)
{
	_Font = NULL;
	Initialize(22);
	this->Number = a;
	this->x = x;
	this->y = y;
	IsFinish = -30;
}

GameFont::~GameFont()
{
	if (_Font != NULL)
	{
		_Font->Release(); 
		_Font = NULL;
	}
}

void GameFont::Initialize(int size)
{
	_FontPosition.top = 0;
	_FontPosition.left = 0;
	_FontPosition.right = Game_ScreenWidth;
	_FontPosition.bottom = Game_ScreenHeight;
	D3DXFONT_DESC FontDesc = { size,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH, "Arial" };

	//create font
	D3DXCreateFontIndirect(Game_Device, &FontDesc, &_Font);
}

void GameFont::Onlost()
{
	_Font->OnLostDevice();
	_Font->OnResetDevice();
}

void GameFont::Render(char* text, float x, float y, D3DCOLOR color)
{
	_FontPosition.left = x;
	_FontPosition.top = y;
	_Font->DrawText(NULL,
		text,
		-1,
		&_FontPosition,
		NULL,
		color); 
}

void GameFont::Render(GameCamera *camera)
{
	Onlost();
	IsFinish++;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_FontPosition.left = pos.x;
	_FontPosition.top = pos.y;
	_Font->DrawText(NULL,
		(char*)to_string(/*Number*/1000).c_str(),
		-1,
		&_FontPosition,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)); //draw text
}

int GameFont::GetFinish()
{
	if (IsFinish > 0) return 1;
	return 0;
}