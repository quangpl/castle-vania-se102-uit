#include "WhipUpgrade.h"

void CWhipUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + WHIP_UPGRADE_BBOX_WIDTH;
	bottom = y + WHIP_UPGRADE_BBOX_HEIGHT;
}

void CWhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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


void CWhipUpgrade::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = ITEM_ANI_WHIP_UPGRADE;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
