#pragma once
#include "GameObject.h"
#include "Constants.h"
#include <iostream>

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CGround : public CGameObject
{
public:

	CGround() 
	{
		setType(TYPE_OBJECT_BACKGROUND);
	}

	virtual void Render() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
};