#pragma once
#include "Items.h"
#define LARGE_HEART_BBOX_WIDTH 10
#define LARGE_HEART_BBOX_HEIGHT 10

#define MONEY_ANI_100 546
#define MONEY_ANI_400 547
#define MONEY_ANI_700 5472
#define MONEY_ANI_1000 5472

#define MONEY_STATE_100 100
#define MONEY_STATE_400 400
#define MONEY_STATE_700 700
#define MONEY_STATE_1000 1000


class CMoney : public CItem
{
	int value = 0; // Gia tri tien cua vat pham : 100,400,700,1000
public:
	CMoney(float x, float y, int _state) : CItem(x, y) {
		SetState(_state);
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);

	void setValue(int _value) { this->value = _value; };
	int getValue() { return this->value; };
};
