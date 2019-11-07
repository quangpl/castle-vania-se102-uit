#include "Weapon.h"
CWeapon* CWeapon::__instance = NULL;
CItems* list_items = CItems::GetInstance();
CCandles* list_candles = CCandles::GetInstance();
CAnimations* list_animations = CAnimations::GetInstance();

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
	else if(typeWeapon== WEAPON_TYPE_DAGGER) {
		left = x + 40;
		right = x + 50;
		if (x <= 0) {
			this->hide();
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
	//isFinishThrowRope();
	if (typeWeapon == WEAPON_TYPE_ROPE) {

		if (list_animations->Get(ROPE_ANI_LEVEL_1)->getCurrentFrame() == 3 || list_animations->Get(ROPE_ANI_LEVEL_2)->getCurrentFrame() == 3 || list_animations->Get(ROPE_ANI_LEVEL_3)->getCurrentFrame() == 3) {
			
			for (int i = 0; i < list_candles->getSize(); i++) {
				list_candles->getByIndex(i)->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
				if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle) && list_candles->getByIndex(i)->isShow()) {

					list_candles->getByIndex(i)->hide();
					int idCandle = list_candles->getByIndex(i)->getId();
					float xCandle, yCandle;
					list_candles->getByIndex(i)->GetPosition(xCandle, yCandle);
					list_items->Get(idCandle)->setTypeItem(list_items->getTypItemFromIndex(idCandle));
					list_items->Get(idCandle)->SetPosition(xCandle, yCandle);
					list_items->Get(idCandle)->SetState(ITEM_STATE_SHOW);
					list_items->Get(idCandle)->setTimeAppear(GetTickCount());
				}
			}
			SetState(WEAPON_STATE_NO_WEAPON);
			list_animations->Get(getCurrentAni())->setCurrentFrame(-1);
		}
}
	else {
			for (int i = 0; i < list_candles->getSize(); i++) {
				list_candles->getByIndex(i)->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
				if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle) && list_candles->getByIndex(i)->isShow()) {

					list_candles->getByIndex(i)->hide();
					int idCandle = list_candles->getByIndex(i)->getId();
					float xCandle, yCandle;
					list_candles->getByIndex(i)->GetPosition(xCandle, yCandle);
					list_items->Get(idCandle)->setTypeItem(list_items->getTypItemFromIndex(idCandle));
					list_items->Get(idCandle)->SetPosition(xCandle, yCandle);
					list_items->Get(idCandle)->SetState(ITEM_STATE_SHOW);
					list_items->Get(idCandle)->setTimeAppear(GetTickCount());
					if (typeWeapon == WEAPON_TYPE_DAGGER) {
						this->setTypeWeapon(WEAPON_TYPE_NO_WEAPON);
						this->hide();
					}
				}
			}
	}
	//Nếu là roi thì roi sẽ dính vào simon
	if (typeWeapon==WEAPON_TYPE_ROPE) {
		CSimon* simon = CSimon::GetInstance();
		this->nx = simon->getDirection();
		simon->GetPosition(this->x, this->y);
	}
	else {
		//WEAPON di chuyển
		x += dx;
	}

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
		setCurrentAni(ani);
	}
}



void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WEAPON_STATE_ROPE:
		typeWeapon = WEAPON_TYPE_ROPE;
		isFinishThrow = true;
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
	CSimon* simon = CSimon::GetInstance();
	this->nx = simon->getDirection();
	simon->GetPosition(this->x, this->y);
	cout << "throw" << endl;
	vx = nx * DAGGER_THROW_SPEED; //Lấy chiều phóng của Simon áp dụng Dagger 
}

bool CWeapon::isFinishThrowRope()
{	

	cout << list_animations->Get(ROPE_ANI_LEVEL_1)->getCurrentFrame() << endl;
	if (isFinishThrow && typeWeapon == WEAPON_TYPE_ROPE) {
		if ( (list_animations->Get(ROPE_ANI_LEVEL_1)->getCurrentFrame() == list_animations->Get(ROPE_ANI_LEVEL_1)->getNumberOfFrame() - 1 || list_animations->Get(ROPE_ANI_LEVEL_2)->getCurrentFrame() == list_animations->Get(ROPE_ANI_LEVEL_2)->getNumberOfFrame() - 1 || list_animations->Get(ROPE_ANI_LEVEL_3)->getCurrentFrame() == list_animations->Get(ROPE_ANI_LEVEL_3)->getNumberOfFrame() - 1)) {
			//setType(WEAPON_TYPE_NO_WEAPON);
			/*if (isFinishThrow) {
				this->SetState(WEAPON_STATE_NO_WEAPON);
			}*/
			//this->setFinishThrow(true);
			SetState(WEAPON_STATE_NO_WEAPON);
			cout << "Da het thoi gian danh" << endl;
			isFinishThrow = false;
			return true;
		}
	}
	return false;
}

