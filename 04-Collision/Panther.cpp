#include "Panther.h"



CPanther::CPanther(float X, float Y, int Direction, CSimon* simon)
{
	vx = vy = 0;
	nx = Direction;
	x = X;
	y = Y;
	//AutoGoX_Backup_X = x;

	isSitting = true;
	isRunning = false;
	isJumping = false;
	this->simon = simon;
	setType(TYPE_OBJECT_ENEMY);

}

void CPanther::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x > BREAK_POINT_DIE_STAGE_2) {
		this->hide();
	}

	//float camX = CGame::GetInstance()->GetCamPos_x();
	////Xoa khi ghost đi khoi camera 
	//if ((x + PANTHER_BBOX_WIDTH > camX + SCREEN_WIDTH && nx == 1) || (x + PANTHER_BBOX_HEIGHT < camX && nx == -1)) {
	//	hide();
	//}

	if (!isShow()) {
		return;
	}


	if (x- simon->GetPositionX() <25 && isSitting) { //distance kich hoat
		isRunning = true;
		isSitting = false;
	}
	if (isSitting) {
		vx = 0;
		SetState(PANTHER_STATE_SITTING);
	}
	if (isJumping) {
		vy = -PANTHER_VY_JUMP;
		vx = -PANTHER_VX_JUMP;
		SetState(PANTHER_STATE_JUMPING);
		isRunning = false;
	}
	if (isRunning) {
		hasStart = true;
		vx = -PANTHER_SPEED_RUNNING;
		if (isLanding)
			vx = -vx;
		SetState(PANTHER_STATE_RUNNING);

	}
	vy += PANTHER_GRAVITY * dt;

	CGameObject::Update(dt);
	// Calculate dx, dy 
	//x += dx;
	//gravity falldown
	
	
	
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
		if (!isJumping && !isSitting) {
			isJumping = true;
			SetState(PANTHER_STATE_JUMPING);
			isRunning = false;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny=0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (ny == -1 && isJumping) 
		{ //va cham ben duoi
			vy = 0;
			vx = -vx;
			vx = 0;
			isJumping = false;
			isRunning = true;
			SetState(PANTHER_STATE_RUNNING);
			isLanding = true;
			if (this->nx != 1) {
				(this->nx) *= -1;
			}
			cout << "Set nx =1" << endl;
		}

		 //Collision logic with Object
		
		//Xử lý sau khi nhảy 

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CPanther::Render()
{
	
	if (!isShow()) {
		cout << "hide panther" << endl;
		return;
	}

	int ani;
	switch (state)
	{
	case PANTHER_STATE_SITTING:
		ani = PANTHER_ANI_SITTING;
		break;
	case PANTHER_STATE_RUNNING:
		ani = PANTHER_ANI_RUNNING;
		break;
	case PANTHER_STATE_JUMPING:
		ani = PANTHER_ANI_JUMPING;
		break;
	default:
		ani = PANTHER_ANI_SITTING;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->RenderFlip(nx, x, y, 15, 255);
	
	if (CGame::GetInstance()->getDebug())
		RenderBoundingBox();

}


CPanther::~CPanther()
{
}
