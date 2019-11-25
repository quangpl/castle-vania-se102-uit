#pragma once
#include "Weapon.h"
#include "Ground.h"
#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 29 //24

#define CANDLE_ANI_SHOW 560 
#define CANDLE_ANI_HIDE 5601
#define CANDLE_STATE_SHOW 1
#define CANDLE_STATE_HIDE 0

#define CANDLE_STATE_HIT 3
#define CANDLE_ANI_HIT 564

#define TIME_HIT 200



class CCandle : public CGround
{
	DWORD startHit;
	int id;
	bool isHit;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
public:
	CCandle()
	{
	}

	void SetState(int state);
	void setId(int id) { this->id = id; };
	int getId() { return this->id; };
	void checkTimeoutHit();
	void hit(DWORD time);
};
