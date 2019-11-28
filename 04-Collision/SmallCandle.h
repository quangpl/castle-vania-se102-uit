#pragma once
#include "Ground.h"

#define SMALL_CANDLE_ANI 559
#define SMALL_CANDLE_BBOX_WIDTH 8
#define SMALL_CANDLE_BBOX_HEIGHT 14
class CSmallCandle : public CGround
{

public:
	CSmallCandle() {

	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};