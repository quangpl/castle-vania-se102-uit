#include "Brick.h"

void CBrick::Render()
{
	CAnimations::GetInstance()->Get(BRICK_ANI)->Render(x, y);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!width && !height) {
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else {
		l = x;
		t = y;
		r = x + width;
		b = y + height;
	}
}