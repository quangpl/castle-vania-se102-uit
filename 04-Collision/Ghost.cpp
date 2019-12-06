#include "Ghost.h"

void CGhost::Render()
{
	CAnimations::GetInstance()->Get(GHOST_ANI)->RenderFlip(getDirection(), x, y, 24, 255);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}


void CGhost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
	//setPositionCustom(x, y-10);
}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	float camX = CGame::GetInstance()->GetCamPos_x();
	if ((x > camX + SCREEN_WIDTH && nx > 0) || (x < camX && nx < 0)) {
		hide();
		cout << "hide" << endl;
	}
	vy += 0.002f * dt;
	vx = nx * GHOST_SPEED;
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
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Object
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj)) {
			//	vy = 0;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

