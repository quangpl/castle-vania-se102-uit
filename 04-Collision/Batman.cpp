#include "Batman.h"

CBatMan::CBatMan()
{
	this->AddAnimation(ANI_BAT_MAN_IDLE);
	this->AddAnimation(ANI_BAT_MAN_FLY);
	this->width = BAT_MAN_WIDTH;
	this->height = BAT_MAN_HEIGHT;
	setType(TYPE_OBJECT_ENEMY);
	this->x = 645;
	this->y = 50;

	yLastFrame = y;

	ani = ANI_ID_BAT_MAN_IDLE;

	status = 0;
	vx = vy = 0;

	isUsingCurve = false;
	isWaiting = false;
	isBossActive = false;
	isActive = true;

	health = 16;

	startSpawnTime = GetTickCount();
}

void CBatMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	DWORD now = GetTickCount();
	
	CSimon::GetInstance()->GetPosition(sx, sy);
	if (sx >= SCENCE_WITDH - SCREEN_WIDTH / 2 && isBossActive == false)
	{
		Start(); // boss chuyển trạng thái
		isBossActive = true;
	}
	if (isBossActive)
	{
		
		CGame::GetInstance()->SetCamPos(SCENCE_WITDH - SCREEN_WIDTH, CGame::GetInstance()->GetCamPos_y());
	}
	float cx, cy;
	cx = CGame::GetInstance()->GetCamPos_x();
	cy = CGame::GetInstance()->GetCamPos_y();

	x += dx;
	y += dy;
	switch (status)
	{
	case BOSS_FLY_START_1:
	{
		if (y >= yTarget)
		{
			status = BOSS_FLY_START_2;

			vy = 0; 

			
			xBefore = x; // lưu lại ví trí đã di chuyển
			yBefore = y;

			xTarget = x + 40;
			yTarget = 161;

			float dTarget = xTarget - xBefore; // Quãng đường từ vị trí hiện tại tới target
			vx = (dTarget / (1000.0f)); // Vận tốc cần để đi đến target trong 1.0s

			vy = 0.12f; // tạo độ cong
		}
		break;
	}
	case BOSS_FLY_START_2:
	{
		if (isWaiting == false)
		{
			// tạo độ cong
			vy -= 0.0001f * dt;


			if (vy < 0)
				vy = 0;

			if (x >= xTarget)
			{
				// di chuyển xong đến ví trí 2
				// cho ngừng bay
				vx = 0;
				vy = 0;


				isWaiting = true; 
				TimeWaited = GetTickCount();
			}
		}
		else
		{
			if (now - TimeWaited >= 1000) // đợi theo thời gian của game
			{

				isWaiting = false; // ngừng chờ

				StartCurves(); 
			}
		}
		break;
	}
	case BOSS_FLY_CURVE:
	{
		/*	--
			-------- Kiểm tra nếu đi đến target thì ngừng bay
			-------- abs(x - xBefore) : quãng đường của boss đã đi được
			-------- abs(xTarget - xBefore) : quãng đường đi đến target
		*/
		float ya = Curve(y1, y2);

		float yb = Curve(y2, y3);

		float yc = Curve(ya, yb);

		vy = (yc - yLastFrame/*Khoảng cách y của frame trước và y dự tính đi*/) / 100; // curve mỗi 100ms
		if (abs(x - xBefore) >= abs(xTarget - xBefore))
		{
			vx = 0;
			vy = 0;
			isUsingCurve = false;

			StartStaight(); // Bắt đầu đi thẳng
			break;
		}

		break;
	}
	case BOSS_FLY_STRAIGHT_1:
	{
	
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore))
		{
			vx = vy = 0;

			StartStaight();

		}
		break;
	}
	case BOSS_FLY_STRAIGHT_2:
	{
		if (isWaiting == false) //Không trong trạng thái chờ
		{
			
			if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
				abs(y - yBefore) >= abs(yTarget - yBefore))
			{
				vx = vy = 0;

				isWaiting = true; // bật trạng thái chờ
				TimeWaited = GetTickCount(); // reset lại time đã chờ
			}
		}
		else
		{
			if (now - TimeWaited >= 1000) // đợi theo thời gian của game
			{
				isWaiting = false;
				int random = rand() % 3;
				switch (random)
				{
				case 0: //	33 %
					isBossAttack = false;
					StartAttack();
					break;

				default: // 66%
					StartCurves();
					break;
				}
			}

		}


		break;
	}
	case BOSS_ATTACK:
	{
		if (isBossAttack)
		{
			//this->makeWeapon = false;
			StartStaight();
		}
		break;
	}
	}


	if (x < cx
		|| cx + SCREEN_WIDTH < x + BAT_MAN_WIDTH //Width cua bosss
		|| y > SCREEN_HEIGHT
		) // ra khỏi cam thì xử lí hướng tiếp theo
	{
		switch (status)
		{
		case BOSS_FLY_CURVE:
		{
			isUsingCurve = false;
			StartStaight();
			break;
		}

		case BOSS_FLY_STRAIGHT_1:
		{
			StartStaight();
			break;
		}

		case BOSS_FLY_STRAIGHT_2:
		{
			int random = rand() % 3;
			switch (random)
			{
			case 0: //	33 %
				isBossAttack = false;
				StartAttack();
				break;

			default: // 66%
				StartCurves();
				break;
			}

			break;
		}
		}
	}

	/*CSimon* simon = CSimon::GetInstance();
	if (this->checkAABBTouch(simon) && simon->getUntouchable() == false)
	{
		if (simon->getDeath() == false)
		{
			simon->TouchEnemy(-simon->nx);
			simon->Damage(1);
		}
	}*/
	yLastFrame = y; 
}


void CBatMan::Start()
{
	status = BOSS_FLY_START_1; 
	ani = ANI_ID_BAT_MAN_FLY;
	vy = 0.05f;
	vx = 0.0f;
	yBefore = y;
	yTarget = y + 20; 
}

void CBatMan::StartCurves()
{

	xBefore = x;
	yBefore = y;

	x1 = x;
	y1 = y;

	x2 = sx;
	y2 = sy + 8;

	if (sx < x) 
		xTarget = BAT_MAN_BOUNDARY_START_STAIGHT_LEFT;
	else 
		xTarget = BAT_MAN_BOUNDARY_START_STAIGHT_RIGHT;

	yTarget = sy - RandomNumber(8, 16);

	x3 = xTarget;
	y3 = yTarget;

	float disNeedToGo = xTarget - xBefore; // quãng đường cần bay
	float directBossToTarget = x - xTarget; // tính hướng bay của boss
	vx = (directBossToTarget / (abs(disNeedToGo) * 1000.0f / 100)) * -1; // vận tốc cần đi đên target // quy ước: cứ 1 giây đi 120px

	isUsingCurve = true;
	status = BOSS_FLY_CURVE;
}

void CBatMan::StartStaight()
{

	switch (status)
	{
	case BOSS_FLY_STRAIGHT_1:
		status = BOSS_FLY_STRAIGHT_2;
		break;
	default:
		status = BOSS_FLY_STRAIGHT_1;
		break;
	}

	xBefore = x;
	yBefore = y;

	xTarget = RandomNumber(BAT_MAN_BOUNDARY_START_STAIGHT_LEFT, BAT_MAN_BOUNDARY_START_STAIGHT_RIGHT);
	yTarget = RandomNumber(100, 200);

	vx = (xTarget - xBefore) / (1000);
	vy = (yTarget - yBefore) / (1000);
}

void CBatMan::StartAttack()
{
	/*if (isBossAttack == false && this->makeWeapon == false)
	{
		vx = vy = 0;
		status = BOSS_ATTACK;
		isBossAttack = true;
		if (y > SCREEN_HEIGHT / 3)
			this->makeWeapon = true;
		if (sx - x > 0)
			nx = 1;
		else
			nx = -1;
	}*/

}

float CBatMan::Curve(float y1, float y2)
{
	
	float percHasGone = abs((x - xBefore) / (xTarget - xBefore));


	
	if (percHasGone < 1)
	{
		percHasGone = percHasGone - (percHasGone / 100);

		float driff = y2 - y1;

		return y1 + (driff * percHasGone);
	}
}

int CBatMan::RandomNumber(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void CBatMan::Render() {
	animations[ani]->Render(x, y);
	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}

void CBatMan::RenderCurrentFrame()
{
	animations[ani]->Render(x, y);
}

bool CBatMan::IsTouchSimon(LPGAMEOBJECT gameObject) {

	if (checkAABBWithObject(gameObject))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(gameObject);
	if (collitionEvent->t >= 0 && collitionEvent->t <= 1.0f)
		return true;

	return false;
}

void CBatMan::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
