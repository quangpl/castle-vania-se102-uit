#pragma once
#include "Effect.h"
#define MONNEY_EFFECT_ANI_100 1546
#define MONNEY_EFFECT_ANI_400 1547
#define MONNEY_EFFECT_ANI_700 1647
#define MONNEY_EFFECT_ANI_1000 604

#define MONNEY_EFFECT_STATE_100 100
#define MONNEY_EFFECT_STATE_400 400
#define MONNEY_EFFECT_STATE_700 700
#define MONNEY_EFFECT_STATE_1000 1000

class CMonneyEffect : public CEffect
{
	int value;
public:
	CMonneyEffect(float x, float y,int _value) : CEffect(x, y) {
		this->value = _value;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};
