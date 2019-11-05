#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include <iostream>
#include "Items.h"

#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 29 //24

#define CANDLE_ANI_SHOW 900 
#define CANDLE_ANI_HIDE 901 

#define CANDLE_STATE_SHOW 1
#define CANDLE_STATE_HIDE 0


class CCandle : public CGameObject
{
public:
	CCandle() : CGameObject()
	{
		setType(TYPE_OBJECT_GROUND);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
};