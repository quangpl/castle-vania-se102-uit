#include "Candle.h"
#include "Simon.h"
void CCandle::Render()
{	
	animations[0]->Render(x,y);
	RenderBoundingBox();
}

void CCandle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}