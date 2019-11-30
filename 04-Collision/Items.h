#ifndef __ITEM_H__
#define	__ITEM_H__
#pragma once
#include "GameObject.h"
#include "Brick.h"



#define SMALL_HEART_BBOX_WIDTH 12
#define SMALL_HEART_BBOX_HEIGHT 12

#define ITEM_STATE_SHOW 1
#define ITEM_STATE_HIDE 0

#define ITEM_ANI_SMALL_HEART 541


#define ITEM_ANI_HIDE 5401

#define FALL_DOWN_SPEED 0.0002f

#define PERIOD_TIME_APPEAR 4000


class CItem : public CGameObject
{
	DWORD timeAppear;
	bool isFinish;
public:
	CItem(float x, float y) : CGameObject()
	{
		setType(TYPE_OBJECT_ITEM); 
		SetPosition(x, y);
		timeAppear = GetTickCount();
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Render() = 0;
	void checkTimeoutAppear();
	void setFinish(bool _finish) { this->isFinish = _finish; };
	bool getFinish() { return this->isFinish; };
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