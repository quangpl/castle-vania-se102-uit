#include "Ghost.h"
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	if (nx<0) {
		if (x <= CGame::GetInstance()->GetCamPos_x()) {
			hide();
			return;
		}
	}
	else {
		if (x >= CGame::GetInstance()->GetCamPos_x() + SCREEN_WIDTH) {
			hide();
			return;
		}
	}
	// Simple fall down
	vy += 0.4f * dt;
	vx = nx * GHOST_SPEED;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	x += dx;

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


		// Collision logic with Object
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CSimon*>(e->obj)) {
				x += dx;
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGhost::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	r = y;
	r = x + GHOST_BBOX_WIDTH;
	b = y + GHOST_BBOX_HEIGHT;
}
void CGhost::Render()
{
	if (!isShow()) {
		return;
	}
	animations[0]->RenderFlip(nx,x, y,24,255); //24: default offset, 255 alpha
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
