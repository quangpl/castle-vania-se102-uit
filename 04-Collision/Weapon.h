#ifndef __WEAPON_H__
#define	__WEAPON_H__
#pragma once
#include "GameObject.h"
#include <iostream>
using namespace std;
#define DAGGER_LEFT 40
#define DAGGER_RIGHT 50

#define WEAPON_TYPE_ROPE 1
#define WEAPON_STATE_ROPE 1

#define WEAPON_TYPE_NO_WEAPON 0
#define WEAPON_STATE_NO_WEAPON 0

#define WEAPON_TYPE_DAGGER 2
#define WEAPON_STATE_DAGGER 2

#define DAGGER_THROW_SPEED 0.2f

#define TIME_THROW 550


class CWeapon : public CGameObject
{
	
	bool isFinish = true;
	DWORD lastTimeAttack;
	int direction;

public:
	CWeapon() : CGameObject()
	{
		setType(TYPE_OBJECT_WEAPON);
	}
	virtual void Render();
	void attack(int direction);
	void setFinish(bool finish) { this->isFinish = finish; };
	bool getFinish() { return this->isFinish; };
	void setDirection(int _direct) { this->direction = _direct; };
	int getDirection() { return this->direction; };
	DWORD getLastTimeAttack() { return this->lastTimeAttack; };
};

#endif