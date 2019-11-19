#pragma once
#include "GameObject.h"


class CHidden : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float w, h;

public:
	CHidden(float w, float h);
};