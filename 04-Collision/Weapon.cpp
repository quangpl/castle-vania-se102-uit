#include "Weapon.h"

//void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	
//	
//	top = y;
//	if(typeWeapon == WEAPON_TYPE_ROPE) {
//		switch (level)
//		{
//		case 1:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_1_LEFT_LTR;
//				right = x + ROPE_LEVEL_1_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_1_RIGHT_RTL;
//				right = x + ROPE_LEVEL_1_LEFT_RTL;
//			}
//			break;
//		case 2:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_2_LEFT_LTR;
//				right = x + ROPE_LEVEL_2_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_2_LEFT_RTL;
//				right = x + ROPE_LEVEL_2_RIGHT_RTL;
//			}
//			break;
//		default:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_3_LEFT_LTR;
//				right = x + ROPE_LEVEL_3_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_3_RIGHT_RTL;
//				right = x + ROPE_LEVEL_3_LEFT_RTL;
//			}
//			break;
//		}
//	}
//	else if(typeWeapon== WEAPON_TYPE_DAGGER) {
//		left = x + DAGGER_LEFT;
//		right = x + DAGGER_RIGHT;
//		if (x <= 0) {
//			this->hide();
//		}
//	}
//	
//	bottom = y + ROPE_BBOX_HEIGHT;
//	setPositionCustom(left, top);
//}

//void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	// Calculate dx, dy 
//	CGameObject::Update(dt);
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//	if (GetTickCount() - timeStartWaitItem >= 4000) {
//		isWaitItem = false;
//	}
//	CalcPotentialCollisions(coObjects, coEvents);
//
//	// reset untouchable timer if untouchable time has passed
//
//	// No collision occured, proceed normally
//	if (coEvents.size() == 0)
//	{
//		x += dx;
//		y += dy;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//
//		// block 
//		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
//		y += min_ty * dy + ny * 0.4f;
//
//		if (nx != 0) vx = 0;
//		if (ny != 0) vy = 0;
//
//		// Collision logic with Object
//		for (UINT i = 0; i < coEventsResult.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEventsResult[i];
//			if (dynamic_cast<CCandle*>(e->obj)) {
//				timeStartWaitItem = GetTickCount();
//				cout << "Va cham" << endl;
//			}
//		}
//	}
//	// clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//}

void CWeapon::Render()
{	
	if (getFinish()) {
		return;
	}
	//cout << CAnimations::GetInstance()->Get(getCurrentAni())->getCurrentFrame() << endl;
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
void CWeapon::attack(float x, float y,int _direction)
{	
	SetPosition(x, y);
	this->direction = _direction;
	isFinish = false;
	lastTimeAttack = GetTickCount(); // lưu lại
	cout << "attack weapon" << endl;
}
//bool CWeapon::canAttack()
//{
//	return  canTa
//}
//
