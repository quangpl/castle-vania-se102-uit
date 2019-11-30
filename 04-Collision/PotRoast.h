#pragma once
#include "Items.h"
#define	 POT_ROAST_BBOX_WIDTH 18
#define  POT_ROAST_BBOX_HEIGHT 14

#define POT_ROAST_ANI 555

class CPotRoast : public CItem
{
public:
	CPotRoast(float x, float y) : CItem(x, y) {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
