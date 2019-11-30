#pragma once
#include "Effect.h"
#define EFFECT_ANI_FIRE 564
class CFire : public CEffect
{
public:
	CFire(float x,float y) : CEffect(x,y) {
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};
