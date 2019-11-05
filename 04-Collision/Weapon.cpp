#include "Weapon.h"
CWeapon* CWeapon::__instance = NULL;
CItems* list_items = CItems::GetInstance();
CCandles* list_candles = CCandles::GetInstance();
CWeapon* CWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapon();
	return __instance;
}
void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	
	top = y;
	if(typeWeapon == WEAPON_TYPE_ROPE) {
		switch (level)
		{
		case 1:
			if (nx > 0) {
				left = x + 42;
				right = x + ROPE_BBOX_LEVEL1_WIDTH;
			}
			else {
				left = x - 13;
				right = x + 5;
			}
			break;
		case 2:
			if (nx > 0) {
				left = x + 48;
				right = x + 69;
			}
			else {
				left = x - 22;
				right = x + 10;
			}
			break;
		default:
			if (nx > 0) {
				left = x + 48;
				right = x + 77;
			}
			else {
				left = x - 28;
				right = x + 5;
			}
			break;
		}
	}

	bottom = y + ROPE_BBOX_HEIGHT;
	setPositionCustom(left, top);
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 

	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	float lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle;
	this->GetBoundingBox(lWeapon, tWeapon, rWeapon, bWeapon);

	/*for (int i = 1; i < coObjects->size(); ++i) {
		if (dynamic_cast<CCandle*>((*coObjects)[i])) {
			(*coObjects)[i]->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
			if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle)) {
				(*coObjects)[i]->hide();
				float xCandle, yCandle;
				int idCandle = dynamic_cast<CCandle*>((*coObjects)[i])->getId();
				(*coObjects)[idCandle]->GetPosition(xCandle, yCandle);
				listItem->Get(idCandle)->setTypeItem(listItem->getTypItemFromIndex(i));
				listItem->Get(idCandle)->SetPosition(xCandle, yCandle);
				listItem->Get(idCandle)->SetState(ITEM_STATE_SHOW);
				listItem->Get(idCandle)->setTimeAppear(GetTickCount());
			}
		}
	
	}*/

	for (int i = 0; i < list_candles->getSize(); i++) {
		list_candles->getByIndex(i)->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
		if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle)&& list_candles->getByIndex(i)->isShow()) {
			list_candles->getByIndex(i)->hide();
			int idCandle = list_candles->getByIndex(i)->getId();
			float xCandle, yCandle;
			list_candles->getByIndex(i)->GetPosition(xCandle, yCandle);
			list_items->Get(idCandle)->setTypeItem(list_items->getTypItemFromIndex(idCandle));
			list_items->Get(idCandle)->SetPosition(xCandle, yCandle);
			list_items->Get(idCandle)->SetState(ITEM_STATE_SHOW);
			list_items->Get(idCandle)->setTimeAppear(GetTickCount());
			list_items->Get(idCandle)->setTimeAppear(GetTickCount());
		}
	}
	//Nếu là roi thì roi sẽ dính vào simon
		
		CSimon* simon = CSimon::GetInstance();
		this->nx = simon->getDirection();
		simon->GetPosition(this->x, this->y);
		//WEAPON chạy theo Simon
		x += dx;
}

void CWeapon::Render()
{	
	int ani;
	
	if (typeWeapon == WEAPON_TYPE_ROPE) {
		switch (level)
		{
		case 1:
			ani = ROPE_ANI_LEVEL_1;
			break;
		case 2:
			ani = ROPE_ANI_LEVEL_2;
			break;	
		case 3:
				ani = ROPE_ANI_LEVEL_3;
				break;
		default:
			ani = ROPE_ANI_LEVEL_1;
			break;
		}
	}
	else if (typeWeapon == WEAPON_TYPE_DAGGER) {
		ani = WEAPON_ANI_DAGGER;
	}
	
	if (typeWeapon) {
		CAnimations::GetInstance()->Get(ani)->RenderFlip(-nx, x, y, 24, 128); // 128 : default alpha
		RenderBoundingBox();
	}
}

void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WEAPON_STATE_ROPE:
		typeWeapon = WEAPON_TYPE_ROPE;
		break;
	case WEAPON_STATE_DAGGER:
		typeWeapon = WEAPON_TYPE_DAGGER;
		cout << "Set state dagger" << endl;
		throwDagger();
		break;
	default:
		typeWeapon = WEAPON_TYPE_NO_WEAPON;
		break;
	}

}
void CWeapon::throwDagger()
{
	cout << "throw" << endl;
	vx = 0.2f;
}
