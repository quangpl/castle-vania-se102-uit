#include "StopWatch.h"

void CStopWatch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + STOP_WATCH_BBOX_WIDTH;
	bottom = y + STOP_WATCH_BBOX_HEIGHT;
}

void CStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CItem::Update(dt, coObjects);
	if (getFinish()) {
		return;
	}
	// Simple fall down
	vy += FALL_DOWN_SPEED * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CStopWatch::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = STOP_WATCH_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
