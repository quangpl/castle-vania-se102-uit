#include "StairPoint.h"

void CStairPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + w;
	bottom = y + h;
}

void CStairPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}
void CStairPoint::Render()
{

	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

