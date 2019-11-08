#pragma once
#include "GameObject.h"
#include <iostream>
#define HIT_EFFECT_ANI 564
#define HIT_EFFECT_TYPE 1
#define TIME_APPEAR 500
class CEffects : public CGameObject
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	DWORD timeStartAppear;
	bool isAppear;
public:
	CEffects() : CGameObject()
	{
		this->AddAnimation(HIT_EFFECT_ANI);
		isAppear = true;
		cout << "new eff" << endl;
	}
	void setTimeStartAppear(DWORD start)
	{
			this->timeStartAppear = start;
	}
	void checkAppear();
};