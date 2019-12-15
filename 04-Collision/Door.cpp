#include "Door.h"


void CDoor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - DOOR_BBOX_PULL_LEFT;
	top = y;
	right = x + DOOR_BBOX_WIDTH;
	bottom = y + DOOR_BBOX_HEIGHT;
}

void CDoor::Update(DWORD dt)
{
	CGameObject::Update(dt);
	/*if (CAnimations::GetInstance()->Get(DOOR_ANI_OPEN)->getCurrentFrame() == 3|| CAnimations::GetInstance()->Get(DOOR_ANI_CLOSE)->getCurrentFrame() == 3)
	{
		isComplete = true;
	}*/
	if (GetTickCount() - timeStartAni >= TIME_TO_FINISH_ANI) {
		isComplete = true;
	}
}
void CDoor::SetState(int state) {
	CGameObject::SetState(state);
	isComplete = false;
	cout << "Set state door: "<< state << endl;
	switch (state)
	{
	case DOOR_STATE_OPEN:
		timeStartAni = GetTickCount();
		isComplete = false;
		break;
	case DOOR_STATE_CLOSE:
		timeStartAni = GetTickCount();
		isComplete = false;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(DOOR_ANI_OPEN)->setCurrentFrame(-1);
	CAnimations::GetInstance()->Get(DOOR_ANI_CLOSE)->setCurrentFrame(-1);
}
void CDoor::Render()
{
	int ani;
	switch (state)
	{
	case DOOR_STATE_OPEN:
		ani = DOOR_ANI_OPEN;
		if (isComplete) {
			ani = DOOR_ANI_OPEN_COMPLETE;
		}
		break;
	case DOOR_STATE_CLOSE:
		ani = DOOR_ANI_CLOSE;
		if (isComplete) {
			ani = DOOR_ANI_CLOSE_COMPLETE;
		}
		break;
	case DOOR_STATE_STATIC:
		ani = DOOR_ANI_STATIC;
		break;
	default:
		break;
	}
	//setCurrentAni(ani);
	CAnimations::GetInstance()->Get(ani)->Render(x, y ,255);
	
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

