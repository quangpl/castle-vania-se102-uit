#include "Effects.h"
#include <iostream>

void CEffects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);\
	checkAppear();
}

void CEffects::Render()
{
	if (isAppear) {
		CAnimations::GetInstance()->Get(HIT_EFFECT_ANI)->Render(x, y);
	}
}

void CEffects::checkAppear()
{
	if (GetTickCount() - timeStartAppear >= TIME_APPEAR) {
		isAppear = false;
		hide();
		cout << "appear false" << endl;
	}
}


