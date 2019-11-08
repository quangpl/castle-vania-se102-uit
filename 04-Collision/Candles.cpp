#include "Candles.h"
#include "Simon.h"

CItems* listItem= CItems::GetInstance();
void CCandle::Render()
{
	int ani = CANDLE_ANI_SHOW;
	if (state == CANDLE_STATE_HIT) {
		ani = CANDLE_ANI_HIT;
	}
	else if (state == CANDLE_STATE_HIDE) {
		ani = CANDLE_ANI_HIDE;
	}
	//if (isShowState) {
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//}
	//RenderBoundingBox();
}
void CCandle::checkTimeoutHit()
{
	if (GetTickCount() - startHit >= TIME_HIT && isHit) {
		cout << "An" << endl;
		SetState(CANDLE_STATE_HIDE);
	}

}
void CCandle::hit(DWORD time)
{
	isHit = true;
	cout << "dang hit" << endl;
	this->startHit = time;
	SetState(CANDLE_STATE_HIT);
}
void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	 //Calculate dx, dy 

CGameObject::Update(dt);

vector<LPCOLLISIONEVENT> coEvents;
vector<LPCOLLISIONEVENT> coEventsResult;

coEvents.clear();
checkTimeoutHit();
float lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle;
for (int i = 0; i < coObjects->size(); i++) {
	if ((*coObjects)[i]->getType() == TYPE_OBJECT_WEAPON) {
		(*coObjects)[i]->GetBoundingBox(lWeapon, tWeapon, rWeapon, bWeapon);
	}
}
}
void CCandle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CANDLE_BBOX_WIDTH;
	b = y + CANDLE_BBOX_HEIGHT;
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_HIDE:
		hide();
		break;
	default:
		show();
		break;
	}
}

CCandles* CCandles::__instance = NULL;


CCandles* CCandles::GetInstance()
{
	if (__instance == NULL) __instance = new CCandles();
	return __instance;
}


void CCandles::Add(CCandle* item)
{
	items.push_back(item);
}

