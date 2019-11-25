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

	CItem::Update(dt, coObjects);
	// Simple fall down
	vy += 0.002f * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (true)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<CCandle*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CCandle* candle = dynamic_cast<CCandle*>(e->obj);
		//		x += dx;
		//		y += dy - 0.1f;
		//		if (y >= Y_BASE) {
		//			y = Y_BASE;
		//		}
		//	}
		//}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CLargeHeart::Render()
{
	CItem::Render();
	int ani = ITEM_ANI_LARGE_HEART;
	CAnimations::GetInstance()->Get(ani)->Render(x,y);
}
