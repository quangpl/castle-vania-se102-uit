#include "Cross.h"

void CCross::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CROSS_BBOX_WIDTH;
	bottom = y + CROSS_BBOX_HEIGHT;
}

void CCross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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


void CCross::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = CROSS_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
