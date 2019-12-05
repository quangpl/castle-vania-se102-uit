#ifndef __WEAPON_H__
#define	__WEAPON_H__
#pragma once
#include "GameObject.h"
#include <iostream>
#include "Candles.h"
#include "Brick.h"
using namespace std;


#define WEAPON_TYPE_ROPE 1
#define WEAPON_STATE_ROPE 1

#define WEAPON_TYPE_NO_WEAPON 0
#define WEAPON_STATE_NO_WEAPON 0

#define WEAPON_TYPE_DAGGER 2
#define WEAPON_STATE_DAGGER 2


#define TIME_THROW 550


class CWeapon : public CGameObject
{
	
	bool isFinish = true;
	DWORD lastTimeAttack;
	int direction;
	DWORD timeStartWaitItem;
	bool canDestroy;
public:
	CWeapon() : CGameObject()
	{
		canDestroy = false;
		setType(TYPE_OBJECT_WEAPON);
	}
	virtual void Render();
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)=0;
	virtual int getCurrentFrame() = 0;
	virtual void setCurrentFrame(int fr) = 0;
	virtual void attack(float x, float y,int direction);
	void setFinish(bool finish) { this->isFinish = finish; };
	bool getFinish() { return this->isFinish; };
	void setDirection(int _direct) { this->direction = _direct; };
	int getDirection() { return this->direction; };
	DWORD getLastTimeAttack() { return this->lastTimeAttack; };
	bool getCanDestroy() { return this->canDestroy; };
	void setCanDestroy(bool _destroy) {this->canDestroy = _destroy; };
	~CWeapon();
};

#endif