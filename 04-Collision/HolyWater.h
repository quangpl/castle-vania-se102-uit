#pragma once
#include "Weapon.h"
#define HOLY_WATER_BBOX_HEIGHT 5
#define HOLY_WATER_BBOX_WIDTH 5

#define HOLY_WATER_ANI 550
#define HOLY_WATER_DISTANCE_THROW_X 42
#define HOLY_WATER_DISTANCE_THROW_Y 23
#define HOLY_WATER_THROW_SPEED 0.15f
#define TIME_FIRING 500
class CHolyWater : public CWeapon
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float startThrowPointX;
	float startThrowPointY;
	int currentFrame;
	bool hasFire;
	DWORD timeFire;
public:
	CHolyWater() {
	};
	void attack(float x, float y, int direction);
	virtual int getCurrentFrame() { return this->currentFrame; };
	virtual void setCurrentFrame(int fr) { this->currentFrame = fr; }
	bool getHasFire() { return this->hasFire; }
};
