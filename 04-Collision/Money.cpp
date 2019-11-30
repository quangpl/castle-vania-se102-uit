#include "Money.h"

void CMoney::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + LARGE_HEART_BBOX_WIDTH;
	bottom = y + LARGE_HEART_BBOX_HEIGHT;
}

void CMoney::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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


void CMoney::Render()
{
	CItem::Render();
	if (getFinish()) {
		return;
	}
	int ani = 0;
	switch (state)
	{
	case MONEY_STATE_100:
		ani = MONEY_ANI_100;
		break;
	case MONEY_STATE_400:
		ani = MONEY_ANI_400;
		break;
	case MONEY_STATE_700:
		ani = MONEY_ANI_700;
		break;
	case MONEY_STATE_1000:
		ani = MONEY_ANI_1000;
		break;
	default:
		break;
	}
	
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
void CMoney::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MONEY_STATE_100:
		value = 100;
		break;
	case MONEY_STATE_400:
		value = 400;
		break;
	case MONEY_STATE_700:
		value = 700;
		break;
	case MONEY_STATE_1000:
		value = 1000;
		break;
	default:
		break;
	}
}
