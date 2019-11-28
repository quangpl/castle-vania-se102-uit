#include "SmallCandle.h"

void CSmallCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SMALL_CANDLE_BBOX_WIDTH;
	bottom = y + SMALL_CANDLE_BBOX_HEIGHT;
}

void CSmallCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CSmallCandle::Render()
{
	int ani = SMALL_CANDLE_ANI; 	
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

