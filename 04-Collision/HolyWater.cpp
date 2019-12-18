#include "HolyWater.h"
void CHolyWater::Render()
{
	int ani = HOLY_WATER_ANI;
	if (getFinish()) {
		return;
	}
	CAnimations::GetInstance()->Get(ani)->RenderFlip(-getDirection(), x, y, 24, 255);
	setCurrentAni(ani);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CHolyWater::attack(float x, float y, int _direction)
{
	setCanDestroy(true);
	setFinish(false);
	CWeapon::attack(x+ _direction*20, y, _direction);
	startThrowPointX = x;
	startThrowPointY = y;
	vx = _direction*HOLY_WATER_THROW_SPEED;
};


void CHolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + HOLY_WATER_BBOX_WIDTH;
	bottom = y + HOLY_WATER_BBOX_HEIGHT;
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//To moving
	if (GetTickCount() - timeFire >= TIME_FIRING) {
		hasFire = false;
	}
	CGameObject::Update(dt);
	if (getFinish()) {
		return;
	}
	
	if (abs(x - startThrowPointX) >= HOLY_WATER_DISTANCE_THROW_X) {
		vx = getDirection()*HOLY_WATER_THROW_SPEED;
		vy = HOLY_WATER_THROW_SPEED;
	}
	if (abs(y - startThrowPointY) >= HOLY_WATER_DISTANCE_THROW_Y) {
		setFinish(true);
		setCanDestroy(false);
		hasFire = true;
		timeFire = GetTickCount();
		vx = 0;
		vy = 0;
	}
	//To moving
	// Calculate dx, dy 

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	if (getFinish()) {
		CalcPotentialCollisions(coObjects, coEvents);
	}


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
				//cout << "cahm brick" << endl;
			}
		}
		//Xử lý sau khi nhảy 

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
};

