#pragma once
#include "GameObject.h"
#include <iostream>
#define BRICK_BBOX_WIDTH  10
#define BRICK_BBOX_HEIGHT 10

class CCandle : public CGameObject
{
public:
	CCandle() : CGameObject()
	{
		setType(TYPE_OBJECT_GROUND);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};