#include "Items.h"

void CItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (typeItem == ITEM_TYPE_WHIP_UPGRADE) {
		right = x + WHIP_UPGRADE_BBOX_WIDTH;
		bottom = y + WHIP_UPGRADE_BBOX_HEIGHT;
	}
	else if (typeItem == ITEM_TYPE_LARGE_HEART) {
		right = x + LARGE_HEART_BBOX_WIDTH;
		bottom = y + LARGE_HEART_BBOX_HEIGHT;
	}
	else if (typeItem == ITEM_TYPE_SMALL_HEART) {
		right = x + SMALL_HEART_BBOX_WIDTH;
		bottom = y + SMALL_HEART_BBOX_HEIGHT;
	}
	else if (typeItem == ITEM_TYPE_DAGGER) {
		right = x + DAGGER_BBOX_WIDTH;
		bottom = y + DAGGER_BBOX_HEIGHT;
	}
	else {
		right = x;
		bottom = y;
	}
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	// Calculate dx, dy 

	CGameObject::Update(dt);
	checkTimeoutAppear(); //check time appear
	//Ngăn không cho Simon rớt ra khỏi màn hình
	if (x <= 0) {
		x = 0;
	}
	// Simple fall down
	vy += 0.002f * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (true)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<CCandle*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CCandle* candle = dynamic_cast<CCandle*>(e->obj);
		//		x += dx;
		//		y += dy - 0.1f;
		//		if (y >= Y_BASE) {
		//			y = Y_BASE;
		//		}
		//	}
		//}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CItem::Render()
{
	int ani;
	if (state == ITEM_STATE_HIDE) {
		ani = ITEM_ANI_HIDE;
	}
	else {
		switch (typeItem)
		{
		case ITEM_TYPE_WHIP_UPGRADE:
			ani = ITEM_ANI_WHIP_UPGRADE;
			break;
		case ITEM_TYPE_LARGE_HEART:
			ani = ITEM_ANI_LARGE_HEART;
			break;
		case ITEM_TYPE_SMALL_HEART:
			ani = ITEM_ANI_SMALL_HEART;
			break;
		case ITEM_TYPE_DAGGER:
			ani = ITEM_ANI_DAGGER;
			break;
		default:
			cout << "vo type hide" << endl;
			ani = ITEM_ANI_HIDE;
			break;
		}
	}

	if (isShowState) {
		CAnimations::GetInstance()->Get(ani)->Render(x, y, 255);

	}
	RenderBoundingBox();
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_HIDE:
		hide();
		break;
	case ITEM_STATE_SHOW:
		show();
		break;
	default:
		break;
	}
}

void CItem::checkTimeoutAppear()
{
	DWORD now = GetTickCount();
	if (now - timeAppear >= PERIOD_TIME_APPEAR) {
		hide();
		SetState(ITEM_STATE_HIDE);
	}
}

CItems* CItems::__instance = NULL;


CItems* CItems::GetInstance()
{
	if (__instance == NULL) __instance = new CItems();
	return __instance;
}


void CItems::Add(int id, CItem* item)
{
	items[id] = item;
}

CItem* CItems::Get(int id)
{
	return items[id];
}

