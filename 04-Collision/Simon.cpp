#include <algorithm>
#include "debug.h"
#include "Constants.h"
#include "Simon.h"
#include "Game.h"
#include "Goomba.h"

CSimon* CSimon::__instance = NULL;


CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	cout << x << endl;
	// Calculate dx, dy 
	CGameObject::Update(dt);
	checkBlink();
	//Ngăn không cho Simon rớt ra khỏi màn hình
	if (x <= 0) {
		x = 0;
	}
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	if (isAutoGoX) {
		autoGoX(directionAutoGoX, SIMON_WALKING_SPEED_AUTO);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	coEvents.clear();
	if (isHit) {
		if (CAnimations::GetInstance()->Get(getCurrentAni())->getCurrentFrame() == CAnimations::GetInstance()->Get(getCurrentAni())->getNumberOfFrame()-1) {
			isHit = false;
			cout << "Set hit false" << endl;
		}
	}
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CItem*>(e->obj) && (dynamic_cast<CItem*>(e->obj)->isShow())) // if e->obj is Item 
			{
				int typeItem = dynamic_cast<CItem*>(e->obj)->collisionWithSimon();
				collisionWithItem(typeItem);
			}
			if (dynamic_cast<CHidden*>(e->obj)) {
				isAutoGoX = true;
				directionAutoGoX = 1;
			}
			
		}
		//Xử lý sau khi nhảy 
		jumpReset();

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;
	
	switch (state)
	{
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_SIT:
		if (isHit) {
			cout << "state sit" << endl;
			ani = SIMON_ANI_SIT_HIT;
		}
		else {
			ani = SIMON_ANI_SIT;
		}
		break;
	case SIMON_STATE_WALKING_BLINK_SINGLE:
		ani = SIMON_ANI_WALKING_BLINK_SINGLE;
		break;
	case SIMON_STATE_JUMP:
		cout << "state jump" << endl;
		ani = SIMON_ANI_JUMP;
		break;
	case SIMON_STATE_HIT:
		ani = SIMON_ANI_HIT;
		if (isSit) {
			ani = SIMON_ANI_SIT_HIT;
		}
		break;
	default:
		
		if (!isJump) {
			
			if (vx == 0)
			{
				if (isHit) {
					ani = SIMON_ANI_HIT;
				}
				else {
					ani = SIMON_ANI_IDLE;
				}
				
			}
			else {
				if (isHit) {
					ani = SIMON_ANI_HIT;
				}
				else {
					ani = SIMON_ANI_WALKING;
				}
			}
		}
		else {
			ani = SIMON_ANI_JUMP;
		}
	break;
	}
	int alpha = 255;
	if (untouchable) alpha = 128;

	CAnimations::GetInstance()->Get(ani)->RenderFlip(-nx,x, y, DEFAULT_OFFSET_X,alpha);
	setCurrentAni(ani);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
void CSimon::goRight() {
	isGoLeft = false;
	isGoRight = true;
	if (!isJump) {
		nx = 1;
	}
	if (!isJump && !isSit && !isHit) {
		vx = SIMON_WALKING_SPEED;
	}
}

void CSimon::goLeft() {
	isGoLeft = true;
	isGoRight = false;
	if (!isJump) {
		nx = -1;
	}
	if (!isJump && !isSit && !isHit) {
		vx = -SIMON_WALKING_SPEED;
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
	cout << "hit hit" << endl;
	isHit = true;
	if ((isGoLeft || isGoRight) && !isJump) {
		vx = 0;
	}
	state = SIMON_STATE_HIT;
}

void CSimon::hitRelease() 
{
		//isHit = false;
}

void CSimon::sitRelease() {
	if (isSit) {
		isSit = false;
		y = y - 10;
	}
}

void CSimon::collisionWithItem(int type) {
	CWeapon* weapon = CWeapon::GetInstance();
	switch (type)
	{
	case ITEM_TYPE_LARGE_HEART:
		cout << "Va cham heart tu simon";
		break;
	case ITEM_TYPE_WHIP_UPGRADE:
		timeStartBlink = GetTickCount();
		weapon->setLevel(weapon->getLevel()+1);
		setFreeze(true);
		setStateBackup(this->state);
		SetState(SIMON_STATE_WALKING_BLINK_SINGLE);
		break;
	case ITEM_TYPE_DAGGER:
		weapon->hide();
		weapon->setHasDagger(true);
		weapon->setTypeWeapon(WEAPON_TYPE_NO_WEAPON);
		break;
	default:
		break;
	}
}

void CSimon::checkBlink() {
	if (getFreeze()) {
		if (GetTickCount() - timeStartBlink > TIME_BLINK) {
			setFreeze(false);
			SetState(getStateBackup());
		}
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
	case SIMON_STATE_HIT:
		hit();
		break;
	case SIMON_STATE_HIT_RELEASE:
		cout << "hit release";
		hitRelease();
		break;
	}
}

void CSimon::autoGoX(int _nx, float speed) {
	nx = _nx;
	vx = 0.1f;
	x += speed*nx;
	isAutoGoX = true;
	//setFreeze(true);
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + SIMON_BBOX_MARGIN_LEFT;
	top = y;
	setPositionCustom(left, top);
	
	right = x + SIMON_BBOX_WIDTH ;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

