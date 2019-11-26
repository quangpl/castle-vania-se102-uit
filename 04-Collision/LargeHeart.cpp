#include "LargeHeart.h"

void CLargeHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	
	right = x + LARGE_HEART_BBOX_WIDTH;
	bottom = y + LARGE_HEART_BBOX_HEIGHT;
}

void CLargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

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


void CLargeHeart::Render()
{
	CItem::Render();
	if (!isShow()) {
		return;
	}
	int ani = ITEM_ANI_LARGE_HEART;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
