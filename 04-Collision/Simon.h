#pragma once
#include "GameObject.h"
#include "Constants.h"
#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200

#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_SIT_RELEASE		501

#define SIMON_STATE_HIT		600
#define SIMON_STATE_HIT_RELEASE 601


#define SIMON_ANI_IDLE_RIGHT		400
#define SIMON_ANI_IDLE_LEFT			401
#define SIMON_ANI_IDLE			500


#define SIMON_ANI_WALKING_RIGHT			500
#define SIMON_ANI_WALKING_LEFT			501
#define SIMON_ANI_WALKING			503


#define SIMON_ANI_JUMP_LEFT			700
#define SIMON_ANI_JUMP_RIGHT		701
#define SIMON_ANI_JUMP		505


#define SIMON_ANI_SIT_LEFT			700
#define SIMON_ANI_SIT_RIGHT		701
#define SIMON_ANI_SIT		505

#define SIMON_ANI_HIT		507
#define SIMON_ANI_SIT_HIT		518



#define SIMON_ANI_DIE				8

#define	SIMON_LEVEL	2

#define SIMON_BBOX_WIDTH  15
#define SIMON_BBOX_HEIGHT 27
#define SIMON_SIT_BBOX_HEIGHT 20


#define SIMON_UNTOUCHABLE_TIME 5000

#define PULL_UP 1

class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	boolean isJump;
	boolean isSit;

	boolean isGoLeft;
	boolean isGoRight;

	boolean isHit;
	boolean canJump = true;
	int stateBackup;
public: 
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL;
		untouchable = 0;
		setType(TYPE_OBJECT_PLAYER);
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
	void sit();
	void sitRelease();
	void hit();
	void hitRelease();




	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};