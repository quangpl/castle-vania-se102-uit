#ifndef __LARGEHEART_H__
#define	__LARGEHEART_H__
#pragma once
#include "Items.h"
#define LARGE_HEART_BBOX_WIDTH 10
#define LARGE_HEART_BBOX_HEIGHT 10

#define ITEM_ANI_LARGE_HEART 542
class CLargeHeart : public CItem
{
public:
	CLargeHeart(float x, float y) : CItem(x, y) {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#endif