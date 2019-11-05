#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Candles.h"

// ROPE
#define ROPE_SPEED_X 0
#define ROPE_SPEED_Y 0
#define ROPE_BBOX_HEIGHT 20
#define ROPE_BBOX_LEVEL1_WIDTH 60
#define ROPE_BBOX_LEVEL2_WIDTH 30
#define ROPE_BBOX_LEVEL3_WIDTH 40

#define ROPE_TIME_LIVE 100

#define ROPE_ANI_LEVEL_1 509
#define ROPE_ANI_LEVEL_2 510
#define ROPE_ANI_LEVEL_3 511

#define WEAPON_ANI_DAGGER 543

#define ROPE_ANI_LEVEL_1_ID 0
#define ROPE_ANI_LEVEL_2_ID 1
#define ROPE_ANI_LEVEL_3_ID 2

#define ROPE_LEVEL_1 1
#define ROPE_LEVEL_2 2
#define ROPE_LEVEL_3 3

#define ROPE_PUSH_TO_RIGHT 32



#define WEAPON_TYPE_ROPE 1
#define WEAPON_STATE_ROPE 1

#define WEAPON_TYPE_NO_WEAPON 0
#define WEAPON_STATE_NO_WEAPON 0

#define WEAPON_TYPE_DAGGER 2
#define WEAPON_STATE_DAGGER 2



class CWeapon : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static CWeapon* __instance;
	int typeWeapon;
	int level;
	bool hasDagger;

public:
	CWeapon() : CGameObject()
	{
		setType(TYPE_OBJECT_WEAPON);
	}

	virtual void SetState(int state);
	static CWeapon* GetInstance();

	void setTypeWeapon(int type) { this->typeWeapon = type; };
	int getTypeWeapon() { return this->typeWeapon; };

	void setLevel(int level) { this->level = level; };
	int getLevel() { return this->level; };
	void throwDagger();

	void setHasDagger(bool _hasDagger) { this->hasDagger = _hasDagger; };
	bool getHasDagger() { return this->hasDagger; };


};