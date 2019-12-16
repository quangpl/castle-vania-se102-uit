#include "SoftBrickEffect.h"

void CSoftBrickEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEffect::Update(dt, coObjects);
}

void CSoftBrickEffect::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	r = y;

	r = x + 50;
	b = y + 50;
}
void CSoftBrickEffect::Render()
{
	if (!isShow()) {
		return;
	}

	CAnimations::GetInstance()->Get(SOFT_BRICK_EFFECT_ANI)->Render(x, y);
}
