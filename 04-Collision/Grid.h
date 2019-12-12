#pragma once
#include "GameObject.h"
#include <set>

#define CELL_WIDTH 60
#define CELL_HEIGHT 80
class CGrid
{
public:
	CGrid();
	void addToGrid(CGameObject* object);

	void getObjectsInGrid(int rowIndex, int colIndex, vector<CGameObject*>& listObjects);

	void getAllObjects(vector<CGameObject*>& listObjects);

	~CGrid();
private:
	vector<LPGAMEOBJECT> cells[10][200];
	set<CGameObject*> listReChecking; //set: each element has to be unique

	int rowIndex;
	int colIndex;
	bool isRevive;
};

