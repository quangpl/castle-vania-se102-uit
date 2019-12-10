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
#include "Maps.h"
#include "Items.h"
#include <sstream> 
#include "Constants.h"
#include "Scenes.h"

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};