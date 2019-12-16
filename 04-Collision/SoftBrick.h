#pragma once
#include "Ground.h"

#define SOFT_BRICK_ANI 16247	
#define SOFT_BRICK_BBOX_WIDTH 16
#define SOFT_BRICK_BBOX_HEIGHT 31
class CSoftBrick : public CGameObject
{

public:
	CSoftBrick(float x,float y) {
		SetPosition(x, y);
	};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};