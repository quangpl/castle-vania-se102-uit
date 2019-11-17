#pragma once
#include <unordered_map>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "debug.h"
#include "Weapon.h"
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
#include "Map.h"
#include "Items.h"
#include <sstream> 
#include "Constants.h"

using namespace std;

class CScene
{
	int id;				// Sprite ID in the sprite database
	LPD3DXSPRITE spriteHandler;
public:
	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void Init(HWND hWnd) = 0;
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

