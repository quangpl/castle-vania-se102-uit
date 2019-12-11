#include "FireBall.h"
#include <iostream>
CFireBall::CFireBall()
{
	
	setType(TYPE_OBJECT_ENEMY);
}
void CFireBall::attack(float _x, float _y, float _nx) {
	this->x = _x;
	this->y = _y;
	this->show();
	this->nx = _nx;
}
void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + FIREBALL_BBOX_WIDTH;
	bottom = y + FIREBALL_BBOX_HEIGHT;
}
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	// vượt quá biên độ trục y cho phép thì đổi chiều vy
	float camX = CGame::GetInstance()->GetCamPos_x();
	/*if ((x > camX + SCREEN_WIDTH && nx > 0) || (x < camX && nx < 0)) {
		this->hide();
	}*/

	CGameObject::Update(dt); // Update dt, dx, dy
	x += dx;
}

void CFireBall::Render()
{
	CAnimations::GetInstance()->Get(FIREBALL_ANI)->RenderFlip(getDirection(), x, y, 4, 255);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
