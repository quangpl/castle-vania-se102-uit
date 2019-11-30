#pragma once
#include "GameObject.h"
#include <iostream>
class CEffect : public CGameObject

{
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	DWORD timeStartAppear;
public:
	CEffect(float x,float y) : CGameObject()
	{
		SetPosition(x, y);
		timeStartAppear = GetTickCount();
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	DWORD getTimeStartAppear() { return this->timeStartAppear; };

};