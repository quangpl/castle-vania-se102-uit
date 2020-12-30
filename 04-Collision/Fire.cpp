#include "Fire.h"

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEffect::Update(dt, coObjects);
}

void CFire::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	r = y;

	r = x + 50;
	b = y + 50;
}
void CFire::Render()
{
	if (!isShow()) {
		return;
	}
	int ani;
	switch (state)
	{
	case FIRE_STATE_NORMAL:
		ani = EFFECT_ANI_FIRE;
		break;
	case FIRE_STATE_POND:
		ani = EFFECT_ANI_POND;
		break;
	default:
		ani = EFFECT_ANI_FIRE;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
