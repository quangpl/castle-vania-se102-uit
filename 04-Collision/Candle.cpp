#include "Candle.h"
#include "Simon.h"

CItems* listItem= CItems::GetInstance();
void CCandle::Render()
{
	int ani = CANDLE_ANI_SHOW;

	if (isShowState) {
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

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
vector<int> listIdItem;
for (int i = 1; i < coObjects->size(); i++) {
	(*coObjects)[i]->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
	if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle)) {
		listIdItem.push_back(i);
		(*coObjects)[i]->hide();
		 float xCandle, yCandle;
		 (*coObjects)[i]->GetPosition(xCandle, yCandle);
		if (i == 1) {
			 listItem->Get(1)->SetPosition(xCandle, yCandle);
			 listItem->Get(1)->setTypeItem(ITEM_TYPE_LARGE_HEART);
			 listItem->Get(1)->SetState(ITEM_STATE_SHOW);
			 listItem->Get(1)->setTimeAppear(GetTickCount());
		}
		
		 if (i == 2) {
			 listItem->Get(2)->SetPosition(xCandle, yCandle);
			 listItem->Get(2)->setTypeItem(ITEM_TYPE_WHIP_UPGRADE);
			 listItem->Get(2)->SetState(ITEM_STATE_SHOW);
			 listItem->Get(2)->setTimeAppear(GetTickCount());

		 }
		 if (i ==3) {
			 listItem->Get(3)->SetPosition(xCandle, yCandle);
			 listItem->Get(3)->setTypeItem(ITEM_TYPE_WHIP_UPGRADE);
			 listItem->Get(3)->SetState(ITEM_STATE_SHOW);
			 listItem->Get(3)->setTimeAppear(GetTickCount());

		 }
		 if (i == 4) {
			 listItem->Get(4)->setTypeItem(ITEM_TYPE_LARGE_HEART);
			 listItem->Get(4)->SetState(ITEM_STATE_SHOW);
			 listItem->Get(4)->SetPosition(xCandle, yCandle);
			 listItem->Get(4)->setTimeAppear(GetTickCount());

		 }
		 if(i==5) {
			 listItem->Get(5)->setTypeItem(ITEM_TYPE_DAGGER);
			 listItem->Get(5)->SetPosition(xCandle, yCandle);
			 listItem->Get(5)->SetState(ITEM_STATE_SHOW);
			 listItem->Get(5)->setTimeAppear(GetTickCount());
		 }
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

