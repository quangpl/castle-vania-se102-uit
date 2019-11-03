#include "Weapon.h"
CWeapon* CWeapon::__instance = NULL;

CWeapon* CWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapon();
	return __instance;
}
void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//if (nx > 0) {
	//	this->SetPosition(x + ROPE_PUSH_TO_RIGHT, y);
	//}
	//else {
	//	this->SetPosition(x + -13, y);
	//}
	left = x;
	top = y;
	switch (typeWeapon)
	{
	case WEAPON_TYPE_ROPE:
		right = x + ROPE_BBOX_LEVEL1_WIDTH;
		bottom = y + ROPE_BBOX_HEIGHT;
	default:
		break;
	}
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	cout << "co va cham" << endl;
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		cout << coEventsResult.size() << endl;

	//	// block 
	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;

	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;

	//	////Collision logic with Goombas
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		if (dynamic_cast<CCandle*>(e->obj)) // if e->obj is Goomba 
	//		{
	//			CCandle* candle = dynamic_cast<CCandle*>(e->obj);
	//			x += dx;
	//			y += dy - 0.1f;
	//			if (y >= Y_BASE) {
	//				y = Y_BASE;
	//			}
	//		}
	//	}

	//}


	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//WEAPON chạy theo Simon
	CSimon* simon = CSimon::GetInstance();
	this->nx = simon->getDirection();
	simon->GetPosition(this->x, this->y);
}

void CWeapon::Render()
{	
	int ani;
	
	if (typeWeapon == WEAPON_TYPE_ROPE) {
		switch (level)
		{
		case 1:
			ani = ROPE_ANI_LEVEL_1;
			break;
		case 2:
			ani = ROPE_ANI_LEVEL_2;
			break;	
		case 3:
				ani = ROPE_ANI_LEVEL_3;
				break;
		default:
			ani = ROPE_ANI_LEVEL_1;
			break;
		}
	}
	
	if (typeWeapon) {
		CAnimations::GetInstance()->Get(ani)->RenderFlip(-nx, x, y, 24, 128); // 128 : default alpha
		RenderBoundingBox();
	}
}

void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WEAPON_STATE_ROPE:
		typeWeapon = WEAPON_TYPE_ROPE;
		break;
	default:
		typeWeapon = WEAPON_TYPE_NO_WEAPON;
		break;
	}

}
