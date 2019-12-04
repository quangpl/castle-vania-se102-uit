#include "Door.h"


void CDoor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOOR_BBOX_WIDTH;
	bottom = y + DOOR_BBOX_HEIGHT;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}
void CDoor::Render()
{
	int ani;
	switch (state)
	{
	case DOOR_STATE_OPEN:
		ani = DOOR_ANI_OPEN;
		break;
	case DOOR_STATE_CLOSE:
		ani = DOOR_ANI_CLOSE;
		break;
	case DOOR_STATE_STATIC:
		ani = DOOR_ANI_STATIC;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y ,255);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

