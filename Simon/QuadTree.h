#ifndef _QUADTREE_H
#define	_QUADTREE_H

#define MAX_OBJECT_IN_REGION	4
#define MAX_OBJECT_ARRAY		2000
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Game.h"
#include "GameSprite.h"
#include "Object.h"
#include "Weapon.h"
#include "GameCamera.h"

using namespace std;

class Nodes 
{
public:
	bool			IsDad;
	bool			HasValue;
	vector<int>		ListIdObj;
	int				id;
	float			x;
	float			y;
	float			width;
	float			height;
	Nodes(int id = 0, float x = 0, float y = 0, float width = 0, float height = 0, bool HasValue = 0);
	~Nodes();
	bool IsContain(Object* Obj);
};

class QuadTree
{
private:
	Nodes *nodes[MAX_OBJECT_ARRAY];
	void  Split(int id, float x, float y, float width, float height);
	int	  NodeNumber;
	vector<Object*> ListObj;
	
public:
	QuadTree(int id, float x, float y, float width, float height, vector<Object*> Obj);
	~QuadTree();

	void Insert(int t, int id);
	void Retrieve(vector<Object*> &ListObj, Object* Obj, int id, GameCamera * camera, int TakeEnemy = 1);
	void WriteQuadTree(char * filename);
	void ReadQuadTree(char *filename);
	void ResetTake(int ResetEnemy = 0);

	int *IsTake;
};

#endif