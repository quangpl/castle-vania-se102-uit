#pragma once
#include "Effect.h"
#define EFFECT_ANI_FIRE 564
#define EFFECT_ANI_POND 552

#define FIRE_STATE_NORMAL 1
#define FIRE_STATE_POND 2
class CFire : public CEffect
{
public:
	CFire(float x,float y) : CEffect(x,y) {
	};
	CFire(float x, float y, int state) : CEffect(x, y) {
		SetState(state);
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};
