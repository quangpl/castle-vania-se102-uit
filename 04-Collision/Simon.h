#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Weapon.h"
#include "Hidden.h"
#include "Candles.h"
#include "Items.h"

#define SIMON_WALKING_SPEED		0.4f //Spped simon walking , default : 0.1f
#define SIMON_WALKING_SPEED_AUTO	0.15f //Spped simon walking , default : 0.1f

//0.1f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_WALKING_BLINK_SINGLE	2001

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
#define SIMON_ANI_WALKING_BLINK_SINGLE		517


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

#define SIMON_BBOX_WIDTH  35
#define SIMON_BBOX_HEIGHT 28
#define SIMON_SIT_BBOX_HEIGHT 20


#define SIMON_UNTOUCHABLE_TIME 5000

#define PULL_UP 1
#define Y_BASE 166.6
#define TIME_BLINK 1300
#define DEFAULT_OFFSET_X 24

#define SIMON_BBOX_MARGIN_LEFT 15

class CSimon : public CGameObject
{
	static CSimon* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;
	boolean isJump;
	boolean isSit;

	boolean isGoLeft;
	boolean isGoRight;

	bool isHit;
	boolean canJump = true;
	int stateBackup;
	DWORD timeStartBlink;

	bool isAutoGoX;
	int directionAutoGoX;
public: 
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL;
		untouchable = 0;
		setType(TYPE_OBJECT_PLAYER);
	}
	static CSimon* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	int getDirection() { return this->nx; }
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

	void collisionWithItem(int type);
	void checkBlink();

	void autoGoX(int nx, float speed);
	void stopAutoGoX() {
		isAutoGoX = false;
	}

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};