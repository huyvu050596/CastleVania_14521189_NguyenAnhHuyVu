#include "Brick.h"

Brick::Brick(float x, float y,float w, float h)
{
	Type = BRICK;
	this->x = x;
	this->y = y;
	this->height = h;
	this->width = w;

	Trend = RIGHT;
	if (State == 1) Size = new GameTexture(BRICK_IMAGE_1, 1, 1, 1, ShowBox);
	if (State == 2) Size = new GameTexture(BRICK_IMAGE_2, 1, 1, 1, ShowBox);

	ObjectSprite = new GameSprite(Size, 1000);
}

Brick::~Brick()
{
}

int CheckPosision(float x, float y)
{
	if (y > 96) return 1;
	return 0;
}

void Brick::DrawObject(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	int row = height / Size->FrameHeight;
	int col = width / Size->FrameWidth;
	int x = pos.x - width / 2 ;
	int y = pos.y + height / 2 ;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (CheckPosision(x, y)) ObjectSprite->Draw(x, y);
			x = x + Size->FrameHeight;
		}
		y = y - Size->FrameHeight;
		x = pos.x - width / 2    ;
	}
}

Box Brick::GetBox(GameCamera *camera, int i)
{
	D3DXVECTOR2 pos = camera->Transform(x - width / 2 - 18 , y + height / 2 - 16);
	return Box(pos.x, pos.y , width - 32, height, 0, 0);
}

float Brick::GetWidth()
{
	return width;
}

float Brick::GetHeight()
{
	return height;
}
