#pragma once
#include "Ground.h"

class CSmallCandle : public CGround
{

public:
	CSmallCandle() {

	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};