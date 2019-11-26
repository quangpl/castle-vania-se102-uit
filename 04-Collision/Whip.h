#ifndef __WHIP_H__
#define	__WHIP_H__
#pragma once
#include "Weapon.h"
//#include "Simon.h"
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


#define ROPE_LEVEL_1_RIGHT_LTR 60
#define ROPE_LEVEL_1_LEFT_LTR 42   // LTR : Left to right
#define ROPE_LEVEL_1_RIGHT_RTL 13
#define ROPE_LEVEL_1_LEFT_RTL 5

#define ROPE_LEVEL_2_RIGHT_LTR 69
#define ROPE_LEVEL_2_LEFT_LTR 48   // LTR : Left to right
#define ROPE_LEVEL_2_RIGHT_RTL 10
#define ROPE_LEVEL_2_LEFT_RTL 22

#define ROPE_LEVEL_3_RIGHT_LTR 77
#define ROPE_LEVEL_3_LEFT_LTR 48  // LTR : Left to right
#define ROPE_LEVEL_3_RIGHT_RTL 28
#define ROPE_LEVEL_3_LEFT_RTL 5

#define TIME_THROW 550


class CWhip : public CWeapon
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int WhipLevel;
	bool wasHit;
public:
	CWhip() {
		wasHit = false;
	};
	void attack(int direction);
	void setLevel(int _level) { this->WhipLevel = _level; };
	int getLevel() { return this->WhipLevel;};
	bool getWasHit() { return this->wasHit; };
};

#endif