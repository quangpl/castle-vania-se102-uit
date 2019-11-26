#include "Candles.h"

//CItems* listItem= CItems::GetInstance();
void CCandle::Render()
{
	int ani;
	ani = CANDLE_ANI_SHOW;
	/*cout << getHealth() << endl;
	if (getHealth()>0) {
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
	}
	else {	
		ani = CANDLE_ANI_SHOW;
	}*/
	if (isShow()) {
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
	}
	if (CGame::GetInstance()->getDebug()) {
			RenderBoundingBox();
	}
}


void CCandle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CANDLE_BBOX_WIDTH;
	b = y + CANDLE_BBOX_HEIGHT;
}


//CCandles* CCandles::__instance = NULL;
//
//
//CCandles* CCandles::GetInstance()
//{
//	if (__instance == NULL) __instance = new CCandles();
//	return __instance;
//}
//
//
//void CCandles::Add(CCandle* item)
//{
//	items.push_back(item);
//}
//
