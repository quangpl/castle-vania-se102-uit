#pragma once
#include "Scenes.h"

#define ID_MAP_1 1
#define ID_MAP_2 2

class CSceneGame : public CScene
{	
	int currentIdMap;
	vector<CGameObject*> objects;
	bool isUpdateScene;
	static CSceneGame* __instance;
public:
	CSceneGame();
	~CSceneGame();

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void checkUpdateScene();
	static CSceneGame* GetInstance();
	void clearObjects() { this->objects.clear(); };
	//void checkCollisonOfSimon();
	void checkCollisonOfWeapon(vector<LPGAMEOBJECT> &objects);
	CItem* getItem(int id, float x, float y);
	void deleteObject(vector<LPGAMEOBJECT> &objects, int index);
	void checkCollisionSimonWithItem();
	void getBonusFromItem(CItem* item);
};
