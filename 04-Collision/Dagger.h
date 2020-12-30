#pragma once
#include "Weapon.h"
#define DAGGER_RIGHT 20
#define DAGGER_BBOX_HEIGHT 20

#define DAGGER_THROW_SPEED 0.2f
#define DAGGER_ANI 543
class CDagger : public CWeapon
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int currentFrame;

public:
	CDagger() {
	};
	void attack(float x, float y, int direction);
	int getCurrentFrame() { return this->currentFrame; };
	void setCurrentFrame(int fr) { this->currentFrame = fr; };
};
