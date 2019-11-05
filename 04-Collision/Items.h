#pragma once
#include "GameObject.h"
#include "Simon.h"


#define WHIP_UPGRADE_BBOX_WIDTH 22
#define WHIP_UPGRADE_BBOX_HEIGHT 22
#define LARGE_HEART_BBOX_WIDTH 10
#define LARGE_HEART_BBOX_HEIGHT 10
#define SMALL_HEART_BBOX_WIDTH 12
#define SMALL_HEART_BBOX_HEIGHT 12
#define DAGGER_BBOX_WIDTH 21
#define DAGGER_BBOX_HEIGHT 14

#define ITEM_TYPE_WHIP_UPGRADE 1
#define ITEM_TYPE_LARGE_HEART 2
#define ITEM_TYPE_SMALL_HEART 3
#define ITEM_TYPE_DAGGER 4

#define ITEM_STATE_SHOW 1
#define ITEM_STATE_HIDE 0

#define ITEM_ANI_WHIP_UPGRADE 540
#define ITEM_ANI_SMALL_HEART 541
#define ITEM_ANI_LARGE_HEART 542
#define ITEM_ANI_DAGGER 543
#define ITEM_ANI_HIDE 5401

#define PERIOD_TIME_APPEAR 5000


class CItem : public CGameObject
{

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int typeItem;
	DWORD timeAppear;
	bool isShow;
public:

	void setTypeItem(int type) { this->typeItem = type; };
	virtual void SetState(int state);
	void setTimeAppear(DWORD time) { this->timeAppear = time; };
	void checkTimeoutAppear();
};


class CItems
{
	static CItems* __instance;

	unordered_map<int, CItem*> items;

public:
	void Add(int id, CItem* item);
	CItem* Get(int id);
	static CItems* GetInstance();
};

