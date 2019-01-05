#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <conio.h>
#include "GameSprite.h"
#include "GameTexture.h"
#include "GameCamera.h"
#include "Global.h"

class Map
{
private:
	GameTexture *TextureTile;

	int ColumnScreen;
	int RowScreen;
	int RowMatrix;
	int ColumnMatrix;
	int ColTile;
	int RowTile;
	int TileFrameCount;
	int TileMap[500][500];

	int row, column;
	int x, y;

public:
	GameSprite *Tile;
	Map();
	~Map();
	void ReadMatrix(char * filename);
	void LoadMap();
	void DrawMap(GameCamera *camera);
	void DrawMap2(LPDIRECT3DDEVICE9 d3ddv,GameCamera *camera);
};

#endif
