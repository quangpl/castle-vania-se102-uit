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
	CAnimations::GetInstance()->Get(EFFECT_ANI_FIRE)->Render(x, y);
}
