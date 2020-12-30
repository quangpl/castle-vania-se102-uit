#pragma once
#include "Effect.h"
#define SOFT_BRICK_EFFECT_ANI 5624

class CSoftBrickEffect : public CEffect
{
public:
	CSoftBrickEffect(float x, float y) : CEffect(x, y) {
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};
