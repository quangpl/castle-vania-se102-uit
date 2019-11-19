#include "Hidden.h"

CHidden::CHidden(float _w, float _h)
{
	setType(TYPE_OBJECT_HIDDEN);
	w = _w;
	h = _h;
}
void CHidden::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + w;
	bottom = y + h;
}

void CHidden::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);


}
void CHidden::Render()
{
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

