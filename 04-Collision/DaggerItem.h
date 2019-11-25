#ifndef __DAGGERITEM_H__
#define	__DAGGERITEM_H__
#pragma once
#include "Items.h"
class CDaggerItem : public CItem
{
public:
	CDaggerItem() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#endif

