#pragma once
#include "Ground.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_ANI 565
#define BRICK_TYPE_1 1
#define BRICK_TYPE_2 2
class CBrick : public CGround

{
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int width, height;
	int typeBrick;
public:
	CBrick() : CGround()
	{
		this->AddAnimation(BRICK_ANI);
		typeBrick = BRICK_TYPE_1;
	}
	CBrick(int type) : CGround()
	{
		this->AddAnimation(BRICK_ANI);
		this->typeBrick = type;
	}
	void setSize(int w, int h) { this->width = w; this->height = h; };
	void setTypeBrick(int type) { this->typeBrick = type; }
	int getTypeBrick() { return this->typeBrick; }
	
};