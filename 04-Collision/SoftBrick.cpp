#include "SoftBrick.h"

void CSoftBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SOFT_BRICK_BBOX_WIDTH;
	bottom = y + SOFT_BRICK_BBOX_HEIGHT;
}

void CSoftBrick::Render()
{
	if (!isShow()) {
		return;
	}
	int ani = SOFT_BRICK_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

