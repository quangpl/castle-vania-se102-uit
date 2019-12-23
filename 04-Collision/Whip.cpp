#include "Whip.h"
void CWhip::Render(int currentId)
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
		ani = ROPE_ANI_LEVEL_3;
		break;
	}
	setCurrentAni(ani);
	CAnimations::GetInstance()->Get(ani)->RenderWhip(currentId,-getDirection(), x, y, 24, 255);

	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CWhip::attack(float x, float y, int direction)
{
	CWeapon::attack(x,y, direction);
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
	//CGameObject::Update(dt);
	CWeapon::Update(dt, coObjects);
	CAnimations* listAnimation = CAnimations::GetInstance();
	/*if (getFinish()) {
		return;
	}*/
	/*if (GetTickCount() - getTimeStartWaitItem() >= 4000) {
		setIsWaitItem(false);
	}*/
	wasHit = false;
	/*if (GetTickCount() - getLastTimeAttack() >= 340) {
		setFinish(true);
		wasHit = true;
	}*/
	//cout << listAnimation->Get(getCurrentAni())->getCurrentFrame() << endl;
	if (getCurrentAni()) {
		currentFrame = listAnimation->Get(getCurrentAni())->getCurrentFrame();
	}
	if (currentFrame ==4) {
		//setFinish(true);
		setCanDestroy(true);
		listAnimation->Get(getCurrentAni())->setCurrentFrame(-1);
		setFinish(true);
	}
	else {
		setCanDestroy(false);
	}
	
	
	/*if(listAnimation->Get(ROPE_ANI_LEVEL_1)->getCurrentFrame()==3|| listAnimation->Get(ROPE_ANI_LEVEL_2)->getCurrentFrame() == 3|| listAnimation->Get(ROPE_ANI_LEVEL_3)->getCurrentFrame() == 3){
		setFinish(true);
		wasHit = true;
	}*/
	//float xSimon, ySimon;
	/*CSimon::GetInstance()->GetPosition(xSimon, ySimon);
	SetPosition(xSimon, ySimon);
	setDirection(CSimon::GetInstance()->getDirection());*/
};

