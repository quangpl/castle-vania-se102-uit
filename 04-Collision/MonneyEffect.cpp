#include "MonneyEffect.h"

void CMonneyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEffect::Update(dt, coObjects);
}

void CMonneyEffect::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	r = y;
	r = x + 53;
	b = y + 53;
}
void CMonneyEffect::Render()
{
	if (!isShow()) {
		return;
	}
	int ani = 0;
	switch (state)
	{
	case MONNEY_EFFECT_STATE_100:
		ani = MONNEY_EFFECT_ANI_100;
		break;
	case MONNEY_EFFECT_STATE_400:
		ani = MONNEY_EFFECT_ANI_400;
		break;
	case MONNEY_EFFECT_STATE_700:
		ani = MONNEY_EFFECT_ANI_700;
		break;
	case MONNEY_EFFECT_STATE_1000:
		ani = MONNEY_EFFECT_ANI_1000;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(601)->Render(x, y);
}
void CMonneyEffect::SetState(int state)
{
	CGameObject::SetState(state);
}

