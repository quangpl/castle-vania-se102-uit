#pragma once
#include "Items.h"
#define HOLY_WATER_BBOX_WIDTH 18
#define HOLY_WATER_BBOX_HEIGHT 18

#define HOLY_WATER_ANI 549

class CHolyWater : public CItem
{
public:
	CHolyWater(float x, float y) : CItem(x, y) {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
