#include <algorithm>
#include "debug.h"
#include "Constants.h"
#include "Simon.h"
#include "Game.h"

#include "Goomba.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	// Calculate dx, dy 

	CGameObject::Update(dt);
	//Ngăn không cho Simon rớt ra khỏi màn hình
	if (x <= 0) {
		x = 0;
	}
	//Không cho simon rớt ra theo chiều x 
	/*if (x > 700) {
		x = 700;
	}*/
	if (y <= BOARD_HEIGHT) {
		y = BOARD_HEIGHT;
	}
	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	if (vy != 0) {
		cout << vy << endl;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
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

		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState()!= GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				vy = -SIMON_JUMP_DEFLECT_SPEED;
		//			}
		//		}
		//		else if (e->nx != 0)
		//		{
		//			if (untouchable==0)
		//			{
		//				if (goomba->GetState()!=GOOMBA_STATE_DIE)
		//				{
		//					if (level > SIMON_LEVEL_SMALL)
		//					{
		//						level = SIMON_LEVEL_SMALL;
		//						StartUntouchable();
		//					}
		//					else 
		//						SetState(SIMON_STATE_DIE);
		//				}
		//			}
		//		}
		//	}
		//}

		//Xử lý sau khi nhảy 
		jumpReset();

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;

	if (state == SIMON_STATE_DIE)
	{
		ani = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_SIT && isSit == true) {
		if (nx > 0) {
			ani = SIMON_ANI_JUMP_RIGHT;
		}
		else {
			ani = SIMON_ANI_JUMP_LEFT;
		}
	}
	//else if (state == SIMON_STATE_HIT && isHit == true) {
	//	if (nx > 0) {
	//		ani = SIMON_ANI_HIT_RIGHT;
	//	}
	//	else {
	//		ani = SIMON_ANI_HIT_LEFT;
	//	}
	//}
	else {
		if (vx == 0)
		{
			if (nx > 0) {
				ani = SIMON_ANI_IDLE_RIGHT;
				if (isJump && !isSit) {
					ani = SIMON_ANI_JUMP_RIGHT;
				}

			}
			else {
				ani = SIMON_ANI_IDLE_LEFT;
				if (isJump && !isSit) {
					ani = SIMON_ANI_JUMP_LEFT;
				}
			}
		}
		else if (vx > 0)
		{
			ani = SIMON_ANI_WALKING_RIGHT;
			if (isJump && !isSit) {
				ani = SIMON_ANI_JUMP_RIGHT;
			}
		}
		else {
			ani = SIMON_ANI_WALKING_LEFT;
			if (isJump && !isSit) {
				ani = SIMON_ANI_JUMP_LEFT;
			}
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	CAnimations::GetInstance()->Get(ani)->Render(x, y, alpha);
	RenderBoundingBox();
}
void CSimon::goRight() {
	if (!isJump && !isSit) {
		vx = SIMON_WALKING_SPEED;
		nx = 1;
	}
}

void CSimon::goLeft() {
	if (!isJump && !isSit) {
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
	}
}

void CSimon::jump() {
	if (canJump&&!isSit) {
		state = SIMON_STATE_JUMP;
		isJump = true;
		canJump = false;
		vy = -SIMON_JUMP_SPEED_Y;
	}
}

void CSimon::jumpReset() {
	
	if (vy <= 0) {
		isJump = false;
	}
	canJump = true;
}

void CSimon::idle() {
	if (!isJump) {
		vx = 0;
	}
}

void CSimon::die() {
	vy = -SIMON_DIE_DEFLECT_SPEED;
}

void CSimon::sit() {
	if (!isJump) {
		isSit = true;
		vx = 0;
	}
}

void CSimon::hit() {
	isHit = true;
}

void CSimon::sitRelease() {
	if (isSit) {
		isSit = false;
		y = y - 10;
	}
}


void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		goRight();
		break;
	case SIMON_STATE_WALKING_LEFT:
		goLeft();
		break;
	case SIMON_STATE_JUMP:
		jump();
		break;
	case SIMON_STATE_IDLE:
		idle();
		break;
	case SIMON_STATE_DIE:
		die();
		break;
	case SIMON_STATE_SIT:
		sit();
		break;
	case SIMON_STATE_SIT_RELEASE:
		sitRelease();
		break;
	/*case SIMON_STATE_HIT:
		hit();
		break;*/
	}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	/*if (level==SIMON_LEVEL_BIG)
	{
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + SIMON_SMALL_BBOX_WIDTH;
		bottom = y + SIMON_SMALL_BBOX_HEIGHT;
	}*/

	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;

	}

}

