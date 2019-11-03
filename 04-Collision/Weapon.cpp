#include "Weapon.h"
CWeapon* CWeapon::__instance = NULL;

CWeapon* CWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapon();
	return __instance;
}
void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (nx > 0) {
		left = x + 42; 
	}
	else {
		left = x - 13;
	}
	
	top = y;
	setPositionCustom(left, top);
	switch (typeWeapon)
	{
	case WEAPON_TYPE_ROPE:
	
		if (nx > 0) {
			right = x + ROPE_BBOX_LEVEL1_WIDTH;
		}
		else {
			right = x + 5;
		}
		bottom = y + ROPE_BBOX_HEIGHT;
	default:
		break;
	}
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 

	CGameObject::Update(dt);

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
