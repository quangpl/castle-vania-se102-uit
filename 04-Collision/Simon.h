#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400

#define SIMON_ANI_IDLE_RIGHT		400
#define SIMON_ANI_IDLE_LEFT			401

#define SIMON_ANI_WALKING_RIGHT			500
#define SIMON_ANI_WALKING_LEFT			501

#define SIMON_ANI_JUMP_LEFT			700
#define SIMON_ANI_JUMP_RIGHT		701



#define SIMON_ANI_DIE				8

#define	SIMON_LEVEL	2

#define SIMON_BBOX_WIDTH  15
#define SIMON_BBOX_HEIGHT 27

#define SIMON_UNTOUCHABLE_TIME 5000


class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	boolean isJump;
	boolean canJump = true;
public: 
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL;
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void goLeft();
	void goRight();
	void jump();
	void jumpReset();
	void idle();
	void die();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};