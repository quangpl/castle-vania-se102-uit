#pragma once
#include "Ground.h"
#define DOOR_ANI_OPEN 561
#define DOOR_ANI_CLOSE 5611
#define DOOR_ANI_STATIC 5612
#define DOOR_ANI_OPEN_COMPLETE 56123
#define DOOR_ANI_CLOSE_COMPLETE 56112

#define DOOR_STATE_OPEN 1
#define DOOR_STATE_CLOSE 2
#define DOOR_STATE_STATIC 0
#define DOOR_STATE_OPEN_COMPLETE 3
#define DOOR_STATE_CLOSE_COMPLETE 4

#define DOOR_BBOX_HEIGHT 40
#define DOOR_BBOX_WIDTH 20

#define DOOR_BBOX_PULL_LEFT 40
#define TIME_TO_FINISH_ANI 400

class CDoor : public CGround
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	virtual void Render();
	bool isComplete;
	DWORD timeStartAni;
	int id; //Id stage se qua

public:
	CDoor(float _x, float _y, int _id) : CGround() {
		setType(TYPE_OBJECT_HIDDEN);
		x = _x;
		y = _y;
		id = _id;
	};
	void Update(DWORD dt);
	void SetState(int state);
	int getId() { return this->id; }
};
