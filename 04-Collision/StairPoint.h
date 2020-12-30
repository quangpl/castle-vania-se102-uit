#pragma once
#include "Ground.h"

class CStairPoint : public CGround
{
	int stairDirection;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	
	float w, h;
	int center;
	float hasThrough; //Simon can through the brick enum: 0,1

public:
	CStairPoint(float _x, float _y, float _w, float _h, int _direction) : CGround() {
		setType(TYPE_OBJECT_HIDDEN);
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		stairDirection = _direction;
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void setStairDirection(int direction) { this->stairDirection = direction; };
	int getStairDirection() { return this->stairDirection; };
	virtual void Render();
	void setCenter(int cen) { this->center = cen; }
	int getCenter() { return this->center; }

	void setHasThrough(float through) { this->hasThrough = through; }
	bool getHasThrough() { return this->hasThrough;}
};