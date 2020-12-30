#include "Grid.h"


CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}
void CGrid::addToGrid(CGameObject* object)
{
	float xObject, yObject;
	object->GetPosition(xObject, yObject);
	float leftObject, topObject, rightObject, bottomObject;
	object->GetBoundingBox(leftObject, topObject, rightObject, bottomObject);

	//Define Object's position from beginning
	int begin_RowMap = yObject / (CELL_HEIGHT);
	int begin_colMap = xObject / (CELL_WIDTH);
	//As above but from the ending
	int end_RowMap = bottomObject / CELL_HEIGHT;
	int end_ColMap = rightObject / CELL_WIDTH;

	for (int i = begin_RowMap; i <= end_RowMap; i++)
	{
		for (int j = begin_colMap; j <= end_ColMap; j++)
		{
			cells[i][j].push_back(object);
		}
	}

}

void CGrid::getObjectsInGrid(int rowIndex, int colIndex, vector<CGameObject*>& listlObjects)
{

	for (int i = 0; i < cells[rowIndex][colIndex].size(); i++)
	{
		if (cells[rowIndex][colIndex].at(i)->isShow() == true)
		{
			if (listReChecking.find(cells[rowIndex][colIndex].at(i)) == listReChecking.end()) //tracking not duplicate
			{
				listReChecking.insert(cells[rowIndex][colIndex].at(i));
				listlObjects.push_back(cells[rowIndex][colIndex].at(i));
			}
		}
		else if (cells[rowIndex][colIndex].at(i)->isShow() == false)
		{
			if (this->isRevive) //reload lại candle/torch khi Simon revive
			{
				cells[rowIndex][colIndex].at(i)->show();
			}
		}
	}

}
void CGrid::getAllObjects(vector<CGameObject*>& listObjects)
{


	listReChecking.clear();
	listObjects.clear(); //making sure our new ListObjects will be cleared

	//Locate Camera on which row and col
	int rowCam = CGame::GetInstance()->GetCamPos_y() / (CELL_HEIGHT);
	int colCam = CGame::GetInstance()->GetCamPos_x() / (CELL_WIDTH);

	//Get fullObjects based on smaller Grid
	for (int j = 0; j <= SCREEN_HEIGHT / CELL_HEIGHT; j++)
	{
		for (int i = 0; i <= SCREEN_WIDTH / CELL_WIDTH; i++)
		{
			getObjectsInGrid(j + rowCam, i + colCam, listObjects);

		}
	}
}

void CGrid::clear()
{
	for (unsigned int i = 0; i < 10; i++)
		for (unsigned int j = 0; j < 200; j++)
			cells[i][j].clear();
}
