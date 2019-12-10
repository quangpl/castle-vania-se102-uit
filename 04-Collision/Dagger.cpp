#include "Dagger.h"
void CDagger::Render()
{
	int ani = DAGGER_ANI;
	if (getFinish()) {
		return;
	}
	CAnimations::GetInstance()->Get(ani)->RenderFlip(-getDirection(), x, y, 8, 255);
	setCurrentAni(ani);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CDagger::attack(float x, float y,int _direction)
{
	setCanDestroy(true);
	CWeapon::attack(x,y,_direction);
	vx = DAGGER_THROW_SPEED * _direction;
};


void CDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + DAGGER_RIGHT;
	bottom = y + DAGGER_BBOX_HEIGHT;
	setPositionCustom(left, top);
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//To moving
	CGameObject::Update(dt);
	if (getFinish()) {
		return;
	}
	if (x <= CGame::GetInstance()->GetCamPos_x() || x >= CGame::GetInstance()->GetCamPos_x() + SCREEN_WIDTH) {
		setFinish(true);
		setCanDestroy(false);
	}
	x += dx;
	//To moving
};

