#include "QuadTreeCollide.h"

QuadTreeCollide::QuadTreeCollide(int level, int id, float x, float y, float width, float height)
{
	this->level = level;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

QuadTreeCollide::~QuadTreeCollide()
{
}

void QuadTreeCollide::Clear()
{
	//Clear all nodes
	if (nodes)
	{
		for (int i = 0; i < 4; i++)
		{
			nodes[i]->Clear();
			delete nodes[i];
		}
		delete[] nodes;
	}

	//Clear current QuadTreeCollide
	ObjectsList->clear();

	delete ObjectsList;
}

// Xác định phạm vi của Obj được truyền vào hàm
bool QuadTreeCollide::IsContain(Object* Obj)
{
	return !(Obj->GetX() + Obj->GetWidth() / 2 < x ||
			 Obj->GetY() + Obj->GetHeight() / 2 < y ||
			 Obj->GetX() - Obj->GetWidth() / 2 > x + width ||
			 Obj->GetY() - Obj->GetHeight() / 2 > y + height);
}

void QuadTreeCollide::Split()
{
	nodes = new QuadTreeCollide*[4];
	nodes[0] = new QuadTreeCollide(level + 1, id * 4 + 1, x, y, width / 2, height / 2);
	nodes[1] = new QuadTreeCollide(level + 1, id * 4 + 2, x + width / 2, y, width / 2, height / 2);
	nodes[2] = new QuadTreeCollide(level + 1, id * 4 + 3, x, y + height / 2, width / 2, height / 2);
	nodes[3] = new QuadTreeCollide(level + 1, id * 4 + 4, x + width / 2, y + height / 2, width / 2, height / 2);
}

void QuadTreeCollide::Insert(Object* Obj)
{
	//Insert Obj into corresponding nodes
	if (nodes)
	{
		if (nodes[0]->IsContain(Obj))
			nodes[0]->Insert(Obj);
		if (nodes[1]->IsContain(Obj))
			nodes[1]->Insert(Obj);
		if (nodes[2]->IsContain(Obj))
			nodes[2]->Insert(Obj);
		if (nodes[3]->IsContain(Obj))
			nodes[3]->Insert(Obj);

		return; // Return here to ignore rest.
	}

	//Insert Obj into current QuadTreeCollide
	if (this->IsContain(Obj)) ObjectsList->push_back(Obj);

	//Split and move all objects in list into it’s corresponding nodes
	if (ObjectsList->size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL)
	{
		Split();

		while (!ObjectsList->empty())
		{
			if (nodes[0]->IsContain(ObjectsList->back())) nodes[0]->Insert(ObjectsList->back());
			if (nodes[1]->IsContain(ObjectsList->back())) nodes[1]->Insert(ObjectsList->back());
			if (nodes[2]->IsContain(ObjectsList->back())) nodes[2]->Insert(ObjectsList->back());
			if (nodes[3]->IsContain(ObjectsList->back())) nodes[3]->Insert(ObjectsList->back());
			ObjectsList->pop_back();
		}
	}
}

void QuadTreeCollide::Retrieve(vector<Object*> *ObjectsList, Object* Obj)
{
	if (nodes)
	{
		if (nodes[0]->IsContain(Obj)) nodes[0]->Retrieve(ObjectsList, Obj);
		if (nodes[1]->IsContain(Obj)) nodes[1]->Retrieve(ObjectsList, Obj);
		if (nodes[2]->IsContain(Obj)) nodes[2]->Retrieve(ObjectsList, Obj);
		if (nodes[3]->IsContain(Obj)) nodes[3]->Retrieve(ObjectsList, Obj);

		return; // Return here to ignore rest.
	}

	//Add all entities in current region into ObjectsList
	if (this->IsContain(Obj))
	{
		for (auto i = ObjectsList->begin(); i != ObjectsList->end(); i++)
		{
			if (Obj != *i) ObjectsList->push_back(*i);
		}
	}
}