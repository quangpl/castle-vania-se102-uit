#pragma once
#include "Ground.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_ANI 565
class CBrick : public CGround

{
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int width, height;
public:
	CBrick() : CGround()
	{
		this->AddAnimation(BRICK_ANI);
	}
	void setSize(int w, int h) { this->width = w; this->height = h; };
	
};