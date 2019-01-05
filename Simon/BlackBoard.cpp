#include "BlackBoard.h"

BlackBoard::BlackBoard()
{
	Size = new GameTexture(IMAGE_FILE, 1, 1, 1,0,0,0);        
	ObjectSprite = new GameSprite(Size, 0);

	this->Stop();
	Trend = 1;
	Type = 31;

	this->x = Game_ScreenWidth / 2 + 20;
	this->y = Size->FrameHeight / 2 + 6;
}

BlackBoard::~BlackBoard()
{
}

void BlackBoard::DrawObject(GameCamera * camera)
{
	ObjectSprite->Draw(x, y);
}
