#ifndef __ITEM_H__
#define	__ITEM_H__
#pragma once
#include "GameObject.h"
#include "Simon.h"


#define WHIP_UPGRADE_BBOX_WIDTH 22
#define WHIP_UPGRADE_BBOX_HEIGHT 16
#define LARGE_HEART_BBOX_WIDTH 10
#define LARGE_HEART_BBOX_HEIGHT 10
#define SMALL_HEART_BBOX_WIDTH 12
#define SMALL_HEART_BBOX_HEIGHT 12
#define DAGGER_BBOX_WIDTH 30
#define DAGGER_BBOX_HEIGHT 8

#define ITEM_STATE_SHOW 1
#define ITEM_STATE_HIDE 0

#define ITEM_ANI_WHIP_UPGRADE 540
#define ITEM_ANI_SMALL_HEART 541
#define ITEM_ANI_LARGE_HEART 542
#define ITEM_ANI_DAGGER 543
#define ITEM_ANI_HIDE 5401

#define PERIOD_TIME_APPEAR 2500


class CItem : public CGameObject
{
	DWORD timeAppear;
public:
	CItem() : CGameObject()
	{
		setType(TYPE_OBJECT_ITEM); 
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;
	void setTimeAppear(DWORD time) { this->timeAppear = time; };
	void checkTimeoutAppear();
};


//class CItems
//{
//	static CItems* __instance;
//
//	unordered_map<int, CItem*> items;
//
//public:
//	void Add(int id, CItem* item);
//	CItem* Get(int id);
//	static CItems* GetInstance();
//	int getTypItemFromIndex(int index);
//};
//
#endif