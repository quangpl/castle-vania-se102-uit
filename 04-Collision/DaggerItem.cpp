#include "DaggerItem.h"

void CDaggerItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void CDaggerItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	// Calculate dx, dy 
	CGameObject::Update(dt);
	CItem::Update(dt, coObjects);

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


void CDaggerItem::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = ITEM_ANI_DAGGER;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
