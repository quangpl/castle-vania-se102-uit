#include "Candle.h"
#include "Simon.h"
void CCandle::Render()
{
	int ani;
	if (!isShow) {
		ani = CANDLE_ANI_HIDE;
	}
	else {
		ani = CANDLE_ANI_SHOW;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x,y);
	RenderBoundingBox();
}

void CCandle::hide()
{
	isShow = false;
}
void CCandle::show()
{
	isShow = true;
}
void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	 //Calculate dx, dy 

	CGameObject::Update(dt);

	 //Calculate dx, dy 

CGameObject::Update(dt);

vector<LPCOLLISIONEVENT> coEvents;
vector<LPCOLLISIONEVENT> coEventsResult;

coEvents.clear();

float lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle;
for (int i = 0; i < coObjects->size(); i++) {
	if ((*coObjects)[i]->getType() == TYPE_OBJECT_WEAPON) {
		(*coObjects)[i]->GetBoundingBox(lWeapon, tWeapon, rWeapon, bWeapon);
	}
}

for (int i = 1; i < coObjects->size(); i++) {
	
	(*coObjects)[i]->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
	if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle)) {
		 dynamic_cast<CCandle*>(coObjects->at(i))->hide();
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

