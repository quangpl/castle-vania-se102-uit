#pragma once
#include "Scenes.h"
#define ID_MAP_1 1
#define ID_MAP_2 2
class CSceneGame : public CScene
{	
	int currentIdMap;
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
};
