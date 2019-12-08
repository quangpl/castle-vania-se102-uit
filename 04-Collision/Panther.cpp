#include "Panther.h"



CPanther::CPanther(float X, float Y, int Direction, float _jumpDistance, CSimon* simon)
{
	vx = vy = 0;
	nx = Direction;
	x = X;
	xBackup = X;
	y = Y;
	//AutoGoX_Backup_X = x;
	jumpDistance = _jumpDistance;

	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	isAutoGoX = 0;

	this->simon = simon;
}

void CPanther::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	if (abs(simon->GetPositionX() - x) <= 20) { //distance kich hoat
		isRunning = 1;
		//cout << "go"<<endl;
		vy = -PANTHER_VYJUMP;
		vx = PANTHER_VXJUMP * nx;
		vx = nx*PANTHER_SPEED_RUNNING;
	}
	//if (isRunning||isSitting) {
	//	//cout << "run"<<endl;
	//	vx = nx*PANTHER_SPEED_RUNNING;
	//}
	//if (isRunning) {
	//	vx = nx * PANTHER_SPEED_RUNNING;
	//	if (abs(x - xBackup) >= 200) {
	//		/*Jump();*/
	//		cout << "Jump" << endl;
	//	}
	//}

	//if (isJumping) {
	//	cout << "jump"<< endl;

	//	if (abs(x - startJumpPoint) >= jumpDistance) {
	//		nx = -nx;
	//		isJumping = 0;
	//		isRunning = 1;
	//	}
	//	else {
	//		vy = -PANTHER_VYJUMP;
	//		vx = PANTHER_VXJUMP * nx;
	//	}
	//}
	// Simple fall down - Gravity of simon
	if (isRunning||isSitting) {
		vy += 0.002f * dt;
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	


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
				cout << "va cham briock" << endl;
				cout << e->obj->GetPositionX() << endl;
				//if (nx < 0) {
				//	if (abs(x - e->obj->GetPositionX())<=2) {
				//		/*Jump();*/
				//		vx = 0;
				//		vy = 0;
				//		cout << "stop" << endl;
				//	}
				//}
				//else {
				//	
				//}
			}


		}
		//Xử lý sau khi nhảy 

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CPanther::Render()
{
	if (!isShow())
		return;
	int ani;
	switch (state)
	{
	case PANTHER_STATE_SITTING:
		ani = PANTHER_ANI_SITTING;
		break;
	case PANTHER_STATE_RUNNINGG:
		ani = PANTHER_ANI_RUNNING;
		break;
	case PANTHER_STATE_JUMPING:
		ani = PANTHER_ANI_JUMPING;
		break;
	default:
		ani = PANTHER_ANI_SITTING;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->RenderFlip(nx, x, y, 20, 255);
	
	if (CGame::GetInstance()->getDebug())
		RenderBoundingBox();

}

bool CPanther::GetIsStart()
{
	return isStart;
}

void CPanther::Jump()
{
	if (isJumping == true)
		return;
	vy = -PANTHER_VYJUMP;
	vx = PANTHER_VXJUMP * nx;
	isJumping = true;
	cout << "Jump" << endl;
	startJumpPoint = x;

}

void CPanther::Run()
{
	vx = PANTHER_SPEED_RUNNING * nx;
	isRunning = 1;
}



CPanther::~CPanther()
{
}
