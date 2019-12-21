#pragma once
#include "Ground.h"
#define HIDDEN_TYPE_DOOR 1
#define HIDDEN_TYPE_STAIR 2
#define HIDDEN_TYPE_GO_TUNNEL 3
#define HIDDEN_TYPE_GO_TUNNEL_2 32

#define HIDDEN_TYPE_STOP_CREATE_GHOST 4

#define HIDDEN_TYPE_CREATE_PANTHER 5
#define HIDDEN_TYPE_SIMON_DIE 6

#define HIDDEN_TYPE_START_CREATE_BAT 7

#define HIDDEN_TYPE_CHANGE_STAGE_FROM_3_TO_2_TYPE_1 8
#define HIDDEN_TYPE_CHANGE_STAGE_FROM_3_TO_2_TYPE_2 9
#define HIDDEN_TYPE_LOAD_STAGE_4 10





class CHidden : public CGround
{
	int typeHidden = HIDDEN_TYPE_DOOR;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

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
	virtual void Render();
	void setTypeHidden(int type) { this->typeHidden = type; };
	int getTypeHidden() { return this->typeHidden; };
};