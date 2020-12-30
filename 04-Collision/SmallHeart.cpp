#include "SmallHeart.h"

void CSmallHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + SMALL_HEART_BBOX_WIDTH;
	bottom = y + SMALL_HEART_BBOX_HEIGHT;
}

void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	if (getFinish()) {
		return;
	}
	if (vy == 0&&timeStartAppear==0) {
		timeStartAppear = GetTickCount();
	}
	
	if (timeStartAppear != 0&&GetTickCount() - timeStartAppear >= PERIOD_TIME_APPEAR) {
		setFinish(true);
	}
	
	// vượt quá biên độ trục x cho phép thì đổi chiều vx
	if (x - xBackup >= DeltaX)
	{
		vx = -SMALLHEART_SPEED_X;
	}
	else
		if (x - xBackup <= -DeltaX)
		{
			vx = SMALLHEART_SPEED_X;
		}



	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
			vx = 0; // cho dừng di chuyển theo biên độ x
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}


void CSmallHeart::Render()
{
	if (getFinish()) {
		return;
	}
	int ani = SMALL_HEART_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
