#pragma once
#include "Items.h"
#define CROSS_BBOX_WIDTH 18
#define CROSS_BBOX_HEIGHT 18

#define CROSS_ANI 553

class CCross : public CItem
{
public:
	CCross(float x, float y) : CItem(x, y) {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
