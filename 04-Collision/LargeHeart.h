#ifndef __LARGEHEART_H__
#define	__LARGEHEART_H__
#pragma once
#include "Items.h"
class CLargeHeart : public CItem
{
public:
	CLargeHeart() {
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#endif