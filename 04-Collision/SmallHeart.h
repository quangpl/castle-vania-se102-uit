#pragma once
#include "Items.h"
#define SMALL_HEART_BBOX_WIDTH 8
#define SMALL_HEART_BBOX_HEIGHT 10

#define SMALL_HEART_ANI 541

#define SMALLHEART_GRAVITY 0.04f
#define SMALLHEART_SPEED_X 0.05f

#define DeltaX 15 //px
class CSmallHeart : public CItem
{
	float xBackup;
	DWORD timeStartAppear;
public:
	CSmallHeart(float x, float y) : CItem(x, y) {
		xBackup = x;
		vy = SMALLHEART_GRAVITY;
		vx = SMALLHEART_SPEED_X;
		timeStartAppear = 0;
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
