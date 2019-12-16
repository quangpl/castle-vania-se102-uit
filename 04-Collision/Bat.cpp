#include "Bat.h"

CBat::CBat(float X, float Y, int Direction)
{
	this->x = X;
	this->y = Y;
	this->yBackup = y;
	this->nx = Direction;
	vy = BAT_SPEED_Y;
	vx = BAT_SPEED_X * Direction;
	setType(TYPE_OBJECT_ENEMY);
}

CBat::~CBat()
{
}

void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	// vượt quá biên độ trục y cho phép thì đổi chiều vy
	float camX = CGame::GetInstance()->GetCamPos_x();
	if ((x > camX + SCREEN_WIDTH && nx > 0) || (x < camX && nx < 0)) {
		hide();
	}
	if (isShow()) {
		return;
	}
	
	
	if (y - yBackup >= DeltaY)
	{
		vy = -BAT_SPEED_Y;
	}
	else
		if (y - yBackup <= -DeltaY)
		{
			vy = BAT_SPEED_Y;
		}


	CGameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;

}

void CBat::Render()
{
	/*if (isShow()) {
		return;
	}*/
	CAnimations::GetInstance()->Get(BAT_ANI)->RenderFlip(getDirection(), x, y, 8, 255);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}
