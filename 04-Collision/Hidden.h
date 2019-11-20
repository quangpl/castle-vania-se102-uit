#pragma once
#include "GameObject.h"

#define HIDDEN_TYPE_DOOR 1
class CHidden : public CGameObject
{
	int typeHidden;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float w, h;

public:
	CHidden(float w, float h, int type);
	void setTypeHidden(int type) { this->typeHidden = type; };
	int getTypeHidden() { return this->typeHidden; };
};