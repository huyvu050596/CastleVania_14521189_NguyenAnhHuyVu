#ifndef _QuadTreeCOLLIDE_H
#define	_QuadTreeCOLLIDE_H

#define MAX_LEVEL                20
#define MAX_OBJECT_IN_REGION     4

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include "Game.h"
#include "GSprite.h"
#include "Object.h"

using namespace std;

extern ofstream	outfile;
class QuadTreeCollide
{
private:
	int             level;
	int				id;
	float			x;
	float			y;
	float			width;
	float			height;

	vector<Object*> *ObjectsList;
	QuadTreeCollide**		nodes;

	bool IsContain(Object* Obj);
	void Split();

public:
	QuadTreeCollide(int level, int id, float left, float bottom, float right, float top);
	~QuadTreeCollide();

	void Clear();
	void Insert(Object* Obj);
	void Retrieve(vector<Object*> *ObjectsList, Object* Obj);
};

#endif