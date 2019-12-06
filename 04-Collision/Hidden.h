#pragma once
#include "Ground.h"
#define HIDDEN_TYPE_DOOR 1
#define HIDDEN_TYPE_STAIR 2
#define HIDDEN_TYPE_GO_TUNNEL 3


class CHidden : public CGround
{
	int typeHidden = HIDDEN_TYPE_DOOR;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float w, h;

public:
	CHidden(float _x,float _y,float _w, float _h,int type) : CGround() {
		setType(TYPE_OBJECT_HIDDEN);
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		typeHidden = type;
	};

	void setTypeHidden(int type) { this->typeHidden = type; };
	int getTypeHidden() { return this->typeHidden; };
};