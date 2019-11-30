#include "HolyWater.h"

void CHolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + HOLY_WATER_BBOX_WIDTH;
	bottom = y + HOLY_WATER_BBOX_HEIGHT;
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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


void CHolyWater::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = HOLY_WATER_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
