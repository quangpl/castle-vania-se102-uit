#pragma once
#include "Scenes.h"

#define ID_MAP_1 1
#define ID_MAP_2 2
#define VX_CAMERA 0.02;

class CSceneGame : public CScene
{	
	int currentIdMap;
	vector<CGameObject*> objects;
	bool isUpdateScene;
	static CSceneGame* __instance;
	bool isStageMoving = false;

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
	void checkCollisionOfSimon();
	void getBonusFromItem(CItem* item);
	void createGhost();
	void checkCollisionOfEnemy();
	void updateCamAutoGo(DWORD dt);
};
