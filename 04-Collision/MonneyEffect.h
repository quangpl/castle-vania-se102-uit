#pragma once
#include "Effect.h"
#define MONNEY_EFFECT_ANI_100 601
#define MONNEY_EFFECT_ANI_400 602
#define MONNEY_EFFECT_ANI_700 603
#define MONNEY_EFFECT_ANI_1000 604

#define MONNEY_EFFECT_STATE_100 100
#define MONNEY_EFFECT_STATE_400 400
#define MONNEY_EFFECT_STATE_700 700
#define MONNEY_EFFECT_STATE_1000 1000

class CMonneyEffect : public CEffect
{
public:
	CMonneyEffect(float x, float y) : CEffect(x, y) {
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void SetState(int state);
};
