#pragma once
#include "Items.h"
#define STOP_WATCH_BBOX_WIDTH 18
#define STOP_WATCH_BBOX_HEIGHT 18

#define STOP_WATCH_ANI 548

class CStopWatch : public CItem
{
public:
	CStopWatch(float x, float y) : CItem(x, y) {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
