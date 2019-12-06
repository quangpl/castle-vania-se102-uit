#include "FishMen.h"


CFishMen::CFishMen(float X, float Y, int Direction, CSimon* simon)
{
	setType(TYPE_OBJECT_ENEMY);
	this->x = X;
	this->y = Y;
	this->nx = Direction;
	vx = 0;
	vy = -FISHMEN_SPEED_Y_UP;
	yInit = y;
	xInit = x;
	xAccumulationAttack = 0;

	cout << "tao fish CONSTRCUTOR" << endl;
	isRunning = 0;
	isAttacking = false;

	this->simon = simon;
	//this->listWeaponOfEnemy = listWeaponOfEnemy;
}

CFishMen::~CFishMen()
{
}

void CFishMen::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 5;
	top = y + 15;
	right = x + FISHMEN_BBOX_WIDTH;
	bottom = y + FISHMEN_BBOX_HEIGHT;
}

void CFishMen::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (y >= BREAK_POINT_DIE_Y&&vy>0) {
		hide();
	}
	if (!isShow()) {
		return;
	}
	if (y <= yInit - FISHMEN_DY_JUMP)
	{
		vy = FISHMEN_SPEED_Y_DOWN;
	}


	if (abs(x - xInit) >= FISHMEN_DX_LIMIT) // đi đủ khoảng cố định
	{
		if ((nx == -1 && !(simon->GetPositionX() < x)) ||
			(nx == 1 && !(x < simon->GetPositionX()))) // đi về hướng của simon mà đã vượt simon thì mới đổi hướng
		{
			nx *= -1; //đổi hướng đi
			xInit = x;
		}
	}


	if (xAccumulationAttack >= FISHMEN_DX_ATTACK_LIMIT)
	{
		xAccumulationAttack = 0;
		attack();
	}

	xBefore = x;


	if (isRunning)
	{
		vx = nx * FISHMEN_SPEED_X;
		vy += FISHMEN_GRAVITY;
	}

	CGameObject::Update(dt);

	// Xu li va cham Brick

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();

	for (UINT i = 0; i < listObject->size(); i++)
	{
		if (dynamic_cast<CBrick*>(listObject->at(i)))
		{
			list_Brick.push_back(listObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_Brick, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	if (ny == -1)
	{
		vy = 0;
		y += min_ty * dy + ny * 0.4f;
		isRunning = true;
	}
	else
	{
		y += dy;
	}

	if (!isAttacking) // đang tấn công thì vẫn cho trọng lực kéo xuống
	{
		bool isCollisionDirectionX = false;
		for (UINT i = 0; i < coEventsResult.size(); i++) // không cho fishmen vượt qua gạch loại nhỏ theo trục x
		{
			if (coEventsResult[i]->nx != 0)
			{
				CBrick* brick = dynamic_cast<CBrick*>(coEventsResult[i]->obj);
				x += min_tx * dx + nx * 0.4f;
				nx *= -1; // quay ngược hướng đi 
				isCollisionDirectionX = true;
			}
		}

		if (!isCollisionDirectionX) // ko va chạm với trục x 
			x += dx;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];


	if (isAttacking)
	{
		DWORD now = GetTickCount();
		if (now - TimeAttack >= FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK)
		{
			isAttacking = false;
		}
	}

	xAfter = x;
	xAccumulationAttack += abs(xAfter - xBefore);

}

void CFishMen::Render()
{
	if (!isShow()) {
		return;
	}
	int ani = FISHMEN_ANI_MOVING;
	CAnimations::GetInstance()->Get(ani)->RenderFlip(nx, x, y, 24, 255);
	if (CGame::GetInstance()->getDebug())
		RenderBoundingBox();
}

void CFishMen::attack()
{
	if (isAttacking)
		return;
	cout << "Attack fish" << endl;
	/*if (weapon == NULL)
	{
		weapon = new FireBall(camera);
		listWeaponOfEnemy->push_back(weapon);
	}*/

	/*if (weapon->GetFinish() == false)
		return;*/

	isAttacking = true;
	TimeAttack = GetTickCount();

	/*weapon->SetSpeed(FIREBALL_SPEED * direction, 0);
	weapon->Attack(x + 10, y + 3, direction);*/

}
