#include "Door.h"


Door::Door(float x, float y, int fit)
{
	Type = DOOR;
	Vx = NO_ACTION;
	Vy = NO_ACTION;
	if (State != 3)
		Size = new GameTexture(DOOR_IMAGE_1, 2, 1, 2);
	else
		Size = new GameTexture(DOOR_IMAGE_2, 2, 1, 2);

	ObjectSprite = new GameSprite(Size, DOOR_FRAME);

	if (State != 3)
		DoorOpen = new GameSprite(new GameTexture("Resources/ground/Gate.png", 2, 1, 2), DOOR_FRAME);
	else
		DoorOpen = new GameSprite(new GameTexture("Resources/ground/Gate2.png", 2, 1, 2), DOOR_FRAME);
	
	Trend = RIGHT;
	this->x = x + Size->FrameWidth*(ReadFileNew == 0);
	this->y = y;

	if (fit) FitPosision();

	if (State == 3 && (x < 250 || y < 250))
	{
		this->x -= 10;
		Type = BRICK;
	}
}

Door::~Door()
{
}

void Door::Update(GameCamera *camera, int t)
{
	if (OpeningTheGate && DoorOpen->_index == 1) OpeningTheGate = 2;
	if (OpeningTheGate && DoorOpen->_index != 1)
	{
		DoorOpen->Update(t);
	}
	else
	ObjectSprite->SelectIndex(0);
}

void Door::DrawObject(GameCamera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (OpeningTheGate) DoorOpen->DrawFlipX(pos.x + Size->FrameWidth, pos.y);
	else ObjectSprite->Draw(pos.x, pos.y);
}

Box Door::GetBox(GameCamera *camera, int i)
{
	D3DXVECTOR2 pos = camera->Transform(x - Size->FrameWidth / 2, y + Size->FrameHeight / 2);
	return Box(pos.x, pos.y, Size->FrameWidth / 2 - 10, Size->FrameHeight, Vx, -Vy);
}
