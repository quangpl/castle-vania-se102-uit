#pragma once
#include <unordered_map>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "debug.h"
#include "Whip.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "tinyxml.h"
#include "Simon.h"
#include "Brick.h"
#include "Goomba.h"
#include "Candles.h"
#include <iostream>
#include <istream>
#include <string>
#include "Maps.h"
//#include "Items.h"
#include <sstream> 
#include "Hidden.h"
#include "Constants.h"
#include "WhipUpgrade.h"
#include "LargeHeart.h"
#include "DaggerItem.h"

using namespace std;

class CScene
{
	int stage;
	int id;				// Sprite ID in the sprite database
	LPD3DXSPRITE spriteHandler;
public:
	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void checkUpdateScene() = 0;
	virtual void clearObjects() = 0;
	void setStage(int _stage) { this->stage = _stage; };
	int getStage() { return this->stage; };
};

typedef CScene* LPSCENE;

class CScenes
{
	static CScenes* __instance;
	unordered_map<int, LPSCENE> scenes;

public:
	void Add(int id,LPSCENE scene);
	LPSCENE Get(int id);
	static CScenes* GetInstance();
};

