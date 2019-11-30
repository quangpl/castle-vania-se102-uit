#pragma once
#include "Effect.h"


void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	if (GetTickCount() - timeStartAppear >= 300) {
		hide();
	}
}
