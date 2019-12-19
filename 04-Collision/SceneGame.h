#pragma once
#include "Scenes.h"

#define ID_MAP_1 1
#define ID_MAP_2 2
#define ID_MAP_3 3
#define ID_MAP_4 4

#define VX_CAMERA 0.02;
#define TIME_CORSS_EFFECT 3000
#define TIME_STOP_WATCH 2500

//Define fishman position
#define FISHMEN_ZONE_1_LEFT 0
#define FISHMEN_ZONE_1_RIGHT 50
#define FISHMEN_POS_1 35

#define FISHMEN_ZONE_2_LEFT 50
#define FISHMEN_ZONE_2_RIGHT 100
#define FISHMEN_POS_2 70

#define FISHMEN_ZONE_3_LEFT 100
#define FISHMEN_ZONE_3_RIGHT 150
#define FISHMEN_POS_3 120

#define FISHMEN_ZONE_4_LEFT 150
#define FISHMEN_ZONE_4_RIGHT 200
#define FISHMEN_POS_4 170 

#define FISHMEN_ZONE_5_LEFT 200
#define FISHMEN_ZONE_5_RIGHT 250
#define FISHMEN_POS_5 230

#define FISHMEN_ZONE_6_LEFT 250
#define FISHMEN_ZONE_6_RIGHT 300
#define FISHMEN_POS_6 270

#define FISHMEN_ZONE_7_LEFT 300
#define FISHMEN_ZONE_7_RIGHT 350
#define FISHMEN_POS_7 330


#define FISHMEN_ZONE_8_LEFT 350
#define FISHMEN_ZONE_8_RIGHT 400
#define FISHMEN_POS_8 370

#define FISHMEN_POS_Y 400


#define BOUNDARY_CAMERA_STAGE_3 427
#define BOUNDARY_CAMERA_STAGE_2 1506

#define TIME_DELAY_CREATE_GHOST 3000
#define TIME_DELAY_CREATE_PANTHER 3000
#define TIME_DELAY_CREATE_BAT 10000




class CSceneGame : public CScene
{	
	int currentIdMap;
	vector<CGameObject*> objects;
	bool isUpdateScene;
	static CSceneGame* __instance;

	bool isStageMoving ;
	bool isWaitSimonThroughScene;
	bool isProcessStageChange ;
	bool isChangeSceneComplete;

	bool hasCrossEffect = false;
	DWORD timeStartCrossEffect;

	bool isStopWatch = false;
	DWORD timeStartStopWatch;

	bool isAllowCreateBat;
	DWORD lastTimeCreateBat;
	bool isWaitingCreateBat = false;


	bool isAllowToCreateGhost;
	DWORD timeStartCreateGhost;
	bool isWaitingToCreateGhost;

	
	bool isAllowToCreatePanther;
	bool isUpdateCreatePantherStatus =false;

	
	bool isAllowCreateFishmen;
	DWORD TimeCreateFishmen;
	DWORD TimeWaitCreateFishmen;
	DWORD timeTest;

public:
	CSceneGame();
	~CSceneGame();
	static CSceneGame* GetInstance();
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void checkUpdateScene();
	

	//void checkCollisonOfSimon();
	void checkCollisonOfWeapon(vector<LPGAMEOBJECT> &objects);
	CItem* getItem(int id, float x, float y);
	void deleteObject(vector<LPGAMEOBJECT> &objects, int index);
	void checkCollisionOfSimon();
	void getBonusFromItem(CItem* item);
	
	//void checkCollisionOfEnemy();

	void checkCollisionSimonWithHidden();
	void updateCamAutoGo(DWORD dt);

	void loadObjectToGrid();
	void clearObjects() { this->objects.clear(); };

	void createBat();
	void createFishMan();
	void createPanther();
	void createGhost();
	void createSplash(float , float y);
};
