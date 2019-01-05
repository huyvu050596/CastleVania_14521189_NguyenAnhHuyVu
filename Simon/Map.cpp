#include "Map.h"

Map::Map()
{
	LoadMap();
}

Map::~Map()
{
}

void Map::ReadMatrix(char * filename)
{
	int i, j;
	FILE *file;
	file = fopen(filename, "r");

	fscanf(file, "%d %d %d %d %d %d", &RowMatrix, &ColumnMatrix, &ColTile, &RowTile, &TileFrameCount, &AutoFit);
	for (i = 0; i < RowMatrix; i++)
	{
		for (j = 0; j < ColumnMatrix; j++)
		{
			fscanf(file, "%d", &TileMap[i][j]);
		}
	}
	fclose(file);
}

void Map::LoadMap()
{
	if (State == -1)
	{
		TextureTile = new GameTexture("Resources/mainmenu.jpg");
		AutoFit = 0;
	}
	if (State == 0)
	{
		TextureTile = new GameTexture("Resources/intro.png");
		AutoFit = 0;
	}
	if (State == 1)
	{
		ReadMatrix("Resources/map/1.B");
		TextureTile = new GameTexture("Resources/map/1.S", ColTile, RowTile, 0);
	}
	if (State == 2)
	{
		ReadMatrix("Resources/map/2.B");
		TextureTile = new GameTexture("Resources/map/2.S", ColTile, RowTile, 0);
	}
	if (State == 3)
	{
		ReadMatrix("Resources/map/3.B");
		TextureTile = new GameTexture("Resources/map/3.S", ColTile, RowTile, 0);
	}
	Game_MapWidth = (TextureTile->FrameHeight)*(ColumnMatrix*(State > 0) + (State == 0));
	Game_MapHeight = (TextureTile->FrameHeight)*(RowMatrix*(State > 0) + (State == 0));
	if (State > 0)
	{
		ColumnScreen = (Game_ScreenWidth) / TextureTile->FrameHeight + 2;
		RowScreen = (Game_ScreenHeight) / TextureTile->FrameHeight + 1;
	}
	Tile = new GameSprite(TextureTile, 0);
}

void Map::DrawMap(GameCamera* camera)
{
	if (State < 1)
	{
		Tile->DrawRaw(0, 0);
		return;
	}

	row = int(camera->viewport.y) / TextureTile->FrameHeight;
	column = int(camera->viewport.x) / TextureTile->FrameHeight;
	
	x = -(int(camera->viewport.x) % TextureTile->FrameHeight);
	y = -(int(camera->viewport.y) % TextureTile->FrameHeight);

	for (int i = 0; i < RowScreen; i++)
	{
		if (y >= AutoFit)
		{
			for (int j = 0; j < ColumnScreen; j++)
			{
				if (!(RowMatrix - row + i < 0 || RowMatrix - row + i > RowMatrix))
				{
					Tile->SelectIndex(TileMap[RowMatrix - row + i][column + j]);
					Tile->DrawRaw(x, y);
					x = x + TextureTile->FrameHeight;
				}
			}
		}
		y = y + TextureTile->FrameHeight;
		x = -int(camera->viewport.x) % TextureTile->FrameHeight;
	}
}

void Map::DrawMap2(LPDIRECT3DDEVICE9 d3ddv,GameCamera* camera)
{
	x = -(int(camera->viewport.x) % TextureTile->FrameHeight);
	y = -(int(camera->viewport.y) % TextureTile->FrameHeight);

	for (int i = 3; i < RowScreen; i++)
	{
		for (int j = 6; j < ColumnScreen; j++)
		{
			if (!(RowMatrix - row + i < 0 || RowMatrix - row + i > RowMatrix))
			{
				Tile->SelectIndex(TileMap[RowMatrix - row + i][column + j]);
				Tile->DrawRaw(x + j*TextureTile->FrameHeight, y + i*TextureTile->FrameHeight);
			}
		}
		x = -int(camera->viewport.x) % TextureTile->FrameHeight;
	}
}



