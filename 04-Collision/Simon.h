#ifndef __SIMON_H__
#define	__SIMON_H__
#pragma once
//#include "GameObject.h"
#include "Constants.h"
#include "Weapon.h"
#include "Whip.h"
//#include "Scenes.h"
#include "Hidden.h"
//#include "Candles.h"
//#include "LargeHeart.h"
//#include "DaggerItem.h"
//#include "WhipUpgrade.h"
#include "Items.h"
#include "StairPoint.h"
//#include <algorithm>
//#include "debug.h"
//#include "Constants.h"
//#include "Game.h"

#define SIMON_WALKING_SPEED		0.25f//Spped simon walking , default : 0.1f
#define SIMON_WALKING_SPEED_AUTO	0.05f //Spped simon walking , default : 0.1f

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

#define SIMON_STATE_ON_STAIR 801

#define SIMON_STATE_HURT 1000




#define SIMON_ANI_IDLE_RIGHT		400
#define SIMON_ANI_IDLE_LEFT			401
#define SIMON_ANI_IDLE			500


#define SIMON_ANI_WALKING_RIGHT			500
#define SIMON_ANI_HURT			501
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

#define SIMON_ANI_STAIR_UP 5000
#define SIMON_ANI_STAIR_DOWN 5004
#define SIMON_ANI_STAIR_ATTACK_UP 5001
#define SIMON_ANI_STAIR_ATTACK_DOWN 5005
#define SIMON_ANI_STAIR_IDLE_UP 5003
#define SIMON_ANI_STAIR_IDLE_DOWN 5002




#define	SIMON_LEVEL	2

#define SIMON_BBOX_WIDTH  35
#define SIMON_BBOX_HEIGHT 28
#define SIMON_SIT_BBOX_HEIGHT 20

#define SIMON_SPEED_ONSTAIR 0.04f;

#define SIMON_UNTOUCHABLE_TIME 5000

#define PULL_UP 1
#define Y_BASE 166.6
#define TIME_BLINK 1000
#define DEFAULT_OFFSET_X 24

#define SIMON_BBOX_MARGIN_LEFT 15
#define TIME_AUTO_GO_STAIR 200
#define TIME_HURT 250
#define TIME_BLINK 2500
#define STAGE_1_TARGET_DOOR 680

#define V_HURT 0.1f;
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
	float targetAutoGoX;
	bool isAutoGoXComplete;

	bool isCollisionWithDoor = false;
	CWeapon* weapon;
	CWeapon* subWeapon;
	DWORD lastTimeAttack;
	LPCOLLISIONEVENT colEventWithItem;

	bool isHitFinish = false;


	bool isGoToStair;
	int typeMovingStair;
	bool canGoStair;
	CStairPoint* currentStair = NULL;
	int currentStairTypeCollision;
	bool isMovingOnStair;
	bool isGoToStartOnStair = false;
	DWORD timeToGoToStartOnStair;
	DWORD timeStartDownStair;
	int centerPointStair;

	bool hasGravity = true;

	bool isHurt;
	DWORD timeStartHurt;
	bool isHurtFinish =true;
	bool isTouchable;
	DWORD timeTouchable;

	bool isBlink;
	DWORD timeStartBlinking;
	int alpha;
	//CItem* itemCollision;
public: 
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL;
		untouchable = 0;
		isHit = false;
		setType(TYPE_OBJECT_PLAYER);
		alpha = 255;
		isTouchable = true;
	}
	static CSimon* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	int getDirection() { return this->nx; };
	void setDirection(int _nx) { this->nx = _nx; };
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

	void checkBlink();
	bool getIsAutoGoXComplete() { return this->isAutoGoXComplete; }
	void autoGoX(int nx, float speed, float target);
	void stopAutoGoX() {
		isAutoGoX = false;
	}
	bool getAutoGoX() {
		return this->isAutoGoX;
	}
	void attack(); //Su dung vu khi chinh
	void attackSub(); //Su dung vu khi phu
	void setWeapon(CWeapon* _weapon) { this->weapon = _weapon; };
	void setSubWeapon(CWeapon* _weapon) { this->subWeapon = _weapon; };
	
	CWeapon* getSubWeapon() {return this->subWeapon; };
	CWeapon* getWeapon() { return this->weapon;};
	bool getIsCollisionWithDoor() { return this->isCollisionWithDoor; };
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	LPCOLLISIONEVENT getCollisionEventWithItem() { return this->colEventWithItem; };
	void collectDagger();
	void collectWhipUpgrade(CWhip* &_whip);
	bool isCollisionWithItem(CItem* item);
	bool getIsHit() { return this->isHit; };
	bool getIsHitFinish() { return this->isHitFinish; };
	void collisionWithHidden(vector<CHidden*> listHidden);
	void collisionWithEnemy(vector<LPGAMEOBJECT> listEnemy);
	void setIsGoToStair(bool stair) { this->isGoToStair = stair; };
	bool getIsGoToStair() { return this->isGoToStair; };

	CStairPoint* checkCollisionStartStair(vector<CStairPoint*> listObj);

	void goOnStair(CStairPoint* listObj);
	void setTypeMovingStair(int type) { this->typeMovingStair = type; }
	int getTypeMovingStair() { return this->typeMovingStair; }

	bool getCanGoStair() { return this->canGoStair; };
	void setCanGoStair(bool stair) { this->canGoStair = stair; };
	void goToStartOnStair();
	void movingOnStair();
	void movingOutStair();
	CStairPoint* getCurrentStair() { return this->currentStair; }
};

#endif