#include "Items.h"

//void CLargeHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	if (typeItem == ITEM_TYPE_WHIP_UPGRADE) {
//		right = x + WHIP_UPGRADE_BBOX_WIDTH;
//		bottom = y + WHIP_UPGRADE_BBOX_HEIGHT;
//	}
//	else if (typeItem == ITEM_TYPE_LARGE_HEART) {
//		right = x + LARGE_HEART_BBOX_WIDTH;
//		bottom = y + LARGE_HEART_BBOX_HEIGHT;
//	}
//	else if (typeItem == ITEM_TYPE_SMALL_HEART) {
//		right = x + SMALL_HEART_BBOX_WIDTH;
//		bottom = y + SMALL_HEART_BBOX_HEIGHT;
//	}
//	else if (typeItem == ITEM_TYPE_DAGGER) {
//		right = x + DAGGER_BBOX_WIDTH;
//		bottom = y + DAGGER_BBOX_HEIGHT;
//	}
//	else {
//		right = x;
//		bottom = y;
//	}
//}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	checkTimeoutAppear(); //check time appear
}


void CItem::Render()
{
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}


void CItem::checkTimeoutAppear()
{
	DWORD now = GetTickCount();
	if (now - timeAppear >= PERIOD_TIME_APPEAR) {
		/*hide();
		SetState(ITEM_STATE_HIDE);
		updateHealth(-2);*/\
		isFinish = true;
	}
}
