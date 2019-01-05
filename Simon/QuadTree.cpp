#include "QuadTree.h"

Nodes::Nodes(int id, float x, float y, float width, float height, bool HasValue)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->IsDad = false; 
	this->HasValue = HasValue;
	ListIdObj.clear();
}

Nodes::~Nodes() 
{
	ListIdObj.clear();
}

bool Nodes::IsContain(Object* Obj)
{
	float X = Obj->GetX();
	float Y = Obj->GetY();
	float W = Obj->GetWidth();
	float H = Obj->GetHeight();
	return !(((X + W/2) < x) || ((Y+H/2) < y) || ((X-W/2) > (x + width)) || ((Y - W / 2)> (y + height)));
}

QuadTree::QuadTree(int id, float x, float y, float width, float height, vector<Object*> Obj)
{
	for (int i = 0; i < MAX_OBJECT_ARRAY; i++) nodes[i] = new Nodes();
	nodes[id] = new Nodes(id, x, y, width, height, 1);
	NodeNumber = 1;
	ListObj = Obj;
	IsTake = new int[ListObj.size()];
	for (int i = 0; i < ListObj.size(); i++) IsTake[i] = false;
}

QuadTree::~QuadTree() 
{
	for (int i = 0; i < MAX_OBJECT_ARRAY; i++)
	{
		if (nodes[i]) delete(nodes[i]);
	}
}

void QuadTree::Split(int id, float x, float y, float width, float height)
{
	nodes[id]->IsDad = 1;
	nodes[id * 4 + 1] = new Nodes(id * 4 + 1, x, y, width / 2, height / 2, 1);
	nodes[id * 4 + 2] = new Nodes(id * 4 + 2, x + width / 2, y, width / 2, height / 2, 1);
	nodes[id * 4 + 3] = new Nodes(id * 4 + 3, x, y + height / 2, width / 2, height / 2, 1);
	nodes[id * 4 + 4] = new Nodes(id * 4 + 4, x + width / 2, y + height / 2, width / 2, height / 2, 1);
}

void QuadTree::Insert(int t,int id)
{
	if (nodes[id]->IsDad)
	{
		for (int i = 1; i <= 4; i++)
		{
			if (nodes[id * 4 + i]->IsContain(ListObj.at(t))) this->Insert(t, id * 4 + i);
		}
		return; 
	}

	if (nodes[id]->IsContain(ListObj.at(t)))
	{
		nodes[id]->ListIdObj.push_back(t);
		NodeNumber++;
	}

	if (((nodes[id]->ListIdObj.size()) > MAX_OBJECT_IN_REGION) && (id * 4 + 4) < MAX_OBJECT_ARRAY)
	{
		Split(id,nodes[id]->x, nodes[id]->y,nodes[id]->width,nodes[id]->height);

		while ((nodes[id]->ListIdObj.size())>0)
		{
			for (int i = 1; i <= 4; i++)
			{
				int t = id * 4 + i;
				if (nodes[t]->IsContain(ListObj.at(nodes[id]->ListIdObj.back()))) this->Insert(nodes[id]->ListIdObj.back(), t);
			}
			nodes[id]->ListIdObj.pop_back();
		}
	}
}

int CheckObj(int Type)                     
{
	if (Type >= 0 && Type <= 9) return 1;   
	if (Type == 26 || Type == 27 || Type == 17) return 1;
	if (Type >= 10 && Type <= 11) return 2;  
	return 0;
}

void QuadTree::Retrieve(vector<Object*> &LObjs, Object* Obj, int id, GameCamera * camera, int TakeEnemy)
{
	if (nodes[id]->IsDad)
	{
		for (int i = 1; i <= 4; i++)
		{
			if (nodes[id * 4 + i]->IsContain(Obj)) this->Retrieve(LObjs, Obj, id * 4 + i,camera, TakeEnemy);
		}
		return;
	}

	if (nodes[id]->IsContain(Obj))
	{
		for (int i = 0; i < nodes[id]->ListIdObj.size(); i++)
		{
			if (IsTake[nodes[id]->ListIdObj.at(i)] == 0)
			{
				if (Obj != ListObj.at(nodes[id]->ListIdObj.at(i)) && ListObj.at(nodes[id]->ListIdObj.at(i))->GetAlive())
				{
					D3DXVECTOR2 pos = camera->Transform(ListObj.at(nodes[id]->ListIdObj.at(i))->GetX(), ListObj.at(nodes[id]->ListIdObj.at(i))->GetY());
					if (pos.y > 64)
					{
						LObjs.push_back(ListObj.at(nodes[id]->ListIdObj.at(i)));
						IsTake[nodes[id]->ListIdObj.at(i)] = 1;
						if (TakeEnemy == 1)
						{
							if (CheckObj(ListObj.at(nodes[id]->ListIdObj.at(i))->GetType()) == 1) IsTake[nodes[id]->ListIdObj.at(i)] = 2;
						}
					}
				}
			}
		}
		
	}
}

void QuadTree::WriteQuadTree(char * filename)
{
	ofstream outfile;
	outfile.open(filename);
	for (int i = 0; i < MAX_OBJECT_ARRAY; i++)
	{
		if (nodes[i]->HasValue)
		{
			outfile << (nodes[i]->id) << " " << nodes[i]->x << " " << nodes[i]->y << " " << nodes[i]->width << " " << nodes[i]->height << " ";
			outfile << int(nodes[i]->IsDad) << " " << nodes[i]->ListIdObj.size() << " ";
			for (int j = 0; j < nodes[i]->ListIdObj.size(); j++)
			{
				outfile << nodes[i]->ListIdObj.at(j) << " ";
			}
			outfile << endl;
		}
	}
	outfile << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0;
	outfile.close();
}

void QuadTree::ReadQuadTree(char * filename)
{
	int id, isdad, size;
	float x, y, w, h;
	int idobj;
	ifstream infile;
	infile.open(filename);
	int i;
	for (i = 0; i < MAX_OBJECT_ARRAY; i++)
	{
		infile >> id >> x >> y >> w >> h >> isdad >> size;
		if (id + x + y + w + h + isdad + size == 0) break;
		nodes[id] = new Nodes(id, x, y, w, h, 1);
		nodes[id]->IsDad = isdad;
		for (int j = 0; j < size; j++)
		{
			infile >> idobj;
			nodes[id]-> ListIdObj.push_back(idobj);
			NodeNumber++;
		}
	}
	infile.close();
}

void QuadTree::ResetTake(int ResetEnemy)
{
	if (ResetEnemy)
	{
		for (int i = 0; i < ListObj.size(); i++)
		{
			IsTake[i] = 0;
		}
	}
	else
	{
		for (int i = 0; i < ListObj.size(); i++)
		{
			if (IsTake[i] == 1) IsTake[i] = 0;
		}
	}
}

