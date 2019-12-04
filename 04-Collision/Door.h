#pragma once
#include "Ground.h"
#define DOOR_ANI_OPEN 561
#define DOOR_ANI_CLOSE 5611
#define DOOR_ANI_STATIC 5612

#define DOOR_STATE_OPEN 1
#define DOOR_STATE_CLOSE 2
#define DOOR_STATE_STATIC 0

#define DOOR_BBOX_HEIGHT 40
#define DOOR_BBOX_WIDTH 8

class CDoor : public CGround
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CDoor(float _x, float _y) : CGround() {
		setType(TYPE_OBJECT_HIDDEN);
		x = _x;
		y = _y;
	};
};