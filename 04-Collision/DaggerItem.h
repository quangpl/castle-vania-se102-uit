#ifndef __DAGGERITEM_H__
#define	__DAGGERITEM_H__
#pragma once
#include "Items.h"
#define DAGGER_BBOX_WIDTH 30
#define DAGGER_BBOX_HEIGHT 8

#define ITEM_ANI_DAGGER 543
class CDaggerItem : public CItem
{
public:
	CDaggerItem(float x, float y) : CItem(x,y){
	
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#endif

