#include "Weapon.h"

//void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	
//	
//	top = y;
//	if(typeWeapon == WEAPON_TYPE_ROPE) {
//		switch (level)
//		{
//		case 1:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_1_LEFT_LTR;
//				right = x + ROPE_LEVEL_1_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_1_RIGHT_RTL;
//				right = x + ROPE_LEVEL_1_LEFT_RTL;
//			}
//			break;
//		case 2:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_2_LEFT_LTR;
//				right = x + ROPE_LEVEL_2_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_2_LEFT_RTL;
//				right = x + ROPE_LEVEL_2_RIGHT_RTL;
//			}
//			break;
//		default:
//			if (nx > 0) {
//				left = x + ROPE_LEVEL_3_LEFT_LTR;
//				right = x + ROPE_LEVEL_3_RIGHT_LTR;
//			}
//			else {
//				left = x - ROPE_LEVEL_3_RIGHT_RTL;
//				right = x + ROPE_LEVEL_3_LEFT_RTL;
//			}
//			break;
//		}
//	}
//	else if(typeWeapon== WEAPON_TYPE_DAGGER) {
//		left = x + DAGGER_LEFT;
//		right = x + DAGGER_RIGHT;
//		if (x <= 0) {
//			this->hide();
//		}
//	}
//	
//	bottom = y + ROPE_BBOX_HEIGHT;
//	setPositionCustom(left, top);
//}

//void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	// Calculate dx, dy 
//
//	CGameObject::Update(dt);
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//
//	float lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle;
//	this->GetBoundingBox(lWeapon, tWeapon, rWeapon, bWeapon);
//	//isFinishThrowRope();
//	if (typeWeapon == WEAPON_TYPE_ROPE) {
//
//		if (list_animations->Get(ROPE_ANI_LEVEL_1)->getCurrentFrame() == 3 || list_animations->Get(ROPE_ANI_LEVEL_2)->getCurrentFrame() == 3 || list_animations->Get(ROPE_ANI_LEVEL_3)->getCurrentFrame() == 3) {
//			
//			for (int i = 0; i < list_candles->getSize(); i++) {
//				list_candles->getByIndex(i)->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
//				if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle) && list_candles->getByIndex(i)->isShow()) {
//					
//					list_candles->getByIndex(i)->hide();
//					list_candles->getByIndex(i)->hit(GetTickCount());
//					int idCandle = list_candles->getByIndex(i)->getId();
//					float xCandle, yCandle;
//					list_candles->getByIndex(i)->GetPosition(xCandle, yCandle);
//					list_items->Get(idCandle)->setTypeItem(list_items->getTypItemFromIndex(idCandle));
//					list_items->Get(idCandle)->SetPosition(xCandle, yCandle);
//					list_items->Get(idCandle)->SetState(ITEM_STATE_SHOW);
//					list_items->Get(idCandle)->setTimeAppear(GetTickCount());
//				}
//			}
//			SetState(WEAPON_STATE_NO_WEAPON);
//			list_animations->Get(getCurrentAni())->setCurrentFrame(-1);
//		}
//}
//	else {
//			for (int i = 0; i < list_candles->getSize(); i++) {
//				list_candles->getByIndex(i)->GetBoundingBox(lCandle, tCandle, rCandle, bCandle);
//				if (checkAABB(lWeapon, tWeapon, rWeapon, bWeapon, lCandle, tCandle, rCandle, bCandle) && list_candles->getByIndex(i)->isShow()) {
//
//					list_candles->getByIndex(i)->hide();
//					list_candles->getByIndex(i)->hit(GetTickCount());
//					int idCandle = list_candles->getByIndex(i)->getId();
//					float xCandle, yCandle;
//					list_candles->getByIndex(i)->GetPosition(xCandle, yCandle);
//					list_items->Get(idCandle)->setTypeItem(list_items->getTypItemFromIndex(idCandle));
//					list_items->Get(idCandle)->SetPosition(xCandle, yCandle);
//					list_items->Get(idCandle)->SetState(ITEM_STATE_SHOW);
//					list_items->Get(idCandle)->setTimeAppear(GetTickCount());
//					if (typeWeapon == WEAPON_TYPE_DAGGER) {
//						this->setTypeWeapon(WEAPON_TYPE_NO_WEAPON);
//						this->hide();
//					}
//				}
//			}
//	}
//	//Nếu là roi thì roi sẽ dính vào simon
//	if (typeWeapon==WEAPON_TYPE_ROPE) {
//		CSimon* simon = CSimon::GetInstance();
//		this->nx = simon->getDirection();
//		simon->GetPosition(this->x, this->y);
//	}
//	else {
//		//WEAPON di chuyển
//		x += dx;
//	}
//
//}

void CWeapon::Render()
{	
	if (getFinish()) {
		return;
	}
	//cout << CAnimations::GetInstance()->Get(getCurrentAni())->getCurrentFrame() << endl;
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
void CWeapon::attack(int _direction)
{
	this->direction = _direction;
	isFinish = false;
	lastTimeAttack = GetTickCount(); // lưu lại
}
//bool CWeapon::canAttack()
//{
//	return  canTa
//}
//
