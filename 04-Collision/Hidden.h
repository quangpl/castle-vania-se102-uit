#pragma once
#include "Ground.h"

#define HIDDEN_TYPE_DOOR 1
class CHidden : public CGround
{
	int typeHidden;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float w, h;

public:
	CHidden(float _w, float _h, int type) : CGround() {
		setType(TYPE_OBJECT_HIDDEN);
		typeHidden = type;
		w = _w;
		h = _h;
	};

	void setTypeHidden(int type) { this->typeHidden = type; };
	int getTypeHidden() { return this->typeHidden; };
};