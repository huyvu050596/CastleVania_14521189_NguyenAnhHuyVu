#include "GameSprite.h"
#include "Global.h"

GameSprite::GameSprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

GameSprite::GameSprite(const GameSprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
	SetARGB();
}

GameSprite::GameSprite(GameTexture* texture, int start, int end, int timeAnimation)
: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
	SetARGB();
}

GameSprite::GameSprite(GameTexture* texture, int timeAnimation)
: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

GameSprite::~GameSprite()
{
	if (_texture != NULL)
		delete _texture;
}

void GameSprite::SetARGB(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

void GameSprite::Next()
{
	_index++;
	if (_index > _end)
		_index = _start;
}

void GameSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void GameSprite::SelectIndex(int index)
{
	_index = index;
}

void GameSprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void GameSprite::Draw(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	//D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	Game_SpriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B) //color
		);
}

void GameSprite::DrawRect(int X, int Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	Game_SpriteHandler->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void GameSprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	Game_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Game_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	this->Draw(x, y);

	Game_SpriteHandler->SetTransform(&oldMt);
}

void GameSprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	Game_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Game_SpriteHandler->SetTransform(&finalMt);

	this->Draw(x, y);

	Game_SpriteHandler->SetTransform(&oldMt);
}

void GameSprite::DrawIndex(int index, int X, int Y)
{
	RECT srect;

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	Game_SpriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(A, R, G, B)  
		);
}

void GameSprite::DrawRaw(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X;
	position.y = Y;
	Game_SpriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B)  
		);
}
int GameSprite::GetIndex()
{
	return _index;
}


void GameSprite::DrawApart(int x, int y, int w)
{
	D3DXMATRIX oldMt;
	Game_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Game_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	{
		int X = x;
		int Y = y;
		RECT srect;

		srect.left = (_index % _texture->Cols)*(_texture->FrameWidth) + _texture->FrameWidth - w;// + 1;
		srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
		srect.right = srect.left + w;
		srect.bottom = srect.top + _texture->FrameHeight;

														 
		D3DXVECTOR3 position(0, 0, 0);
		D3DXVECTOR3 center(0, 0, 0);
		position.x = X - _texture->FrameWidth / 2;
		position.y = Y - _texture->FrameHeight / 2;
		Game_SpriteHandler->Draw(
			_texture->Texture,
			&srect,
			&center,
			&position,
			D3DCOLOR_XRGB(A, R, G, B)  
		);
	}
	
	Game_SpriteHandler->SetTransform(&oldMt);
}