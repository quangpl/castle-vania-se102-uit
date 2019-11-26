#include "Whip.h"
void CWhip::Render()
{
	int ani;
	if (getFinish()) {
		return;
	}
	switch (WhipLevel)
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
		break;
	}
	CAnimations::GetInstance()->Get(ani)->RenderFlip(-getDirection(), x, y, 24, 128);
	setCurrentAni(ani);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CWhip::attack(int _direction)
{
	CWeapon::attack(_direction);
};


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	
		switch (WhipLevel)
		{
		case 1:
			if (getDirection() > 0) {
				left = x + ROPE_LEVEL_1_LEFT_LTR;
				right = x + ROPE_LEVEL_1_RIGHT_LTR;
			}
			else {
				left = x - ROPE_LEVEL_1_RIGHT_RTL;
				right = x + ROPE_LEVEL_1_LEFT_RTL;
			}
			break;
		case 2:
			if (getDirection() > 0) {
				left = x + ROPE_LEVEL_2_LEFT_LTR;
				right = x + ROPE_LEVEL_2_RIGHT_LTR;
			}
			else {
				left = x - ROPE_LEVEL_2_LEFT_RTL;
				right = x + ROPE_LEVEL_2_RIGHT_RTL;
			}
			break;
		default:
			if (getDirection() > 0) {
				left = x + ROPE_LEVEL_3_LEFT_LTR;
				right = x + ROPE_LEVEL_3_RIGHT_LTR;
			}
			else {
				left = x - ROPE_LEVEL_3_RIGHT_RTL;
				right = x + ROPE_LEVEL_3_LEFT_RTL;
			}
			break;
		}
	bottom = y + ROPE_BBOX_HEIGHT;
	setPositionCustom(left, top);
};


void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	

	if (getFinish()) {
		return;
	}
	wasHit = false;
	if (GetTickCount() - getLastTimeAttack() >= 340) {
		setFinish(true);
		wasHit = true;
	}
	float xSimon, ySimon;
	/*CSimon::GetInstance()->GetPosition(xSimon, ySimon);
	SetPosition(xSimon, ySimon);
	setDirection(CSimon::GetInstance()->getDirection());*/
};

