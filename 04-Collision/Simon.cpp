#include "Simon.h"

CSimon* CSimon::__instance = NULL;


CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}
void CSimon::goOnStair(CStairPoint* stairPoint) {
	switch (stairPoint->getStairDirection())
	{
	case 1:
		nx = 1;
		//autoGoX(1, SIMON_WALKING_SPEED_AUTO, 5900);
		/*if (nx > 0) {
			vx = SIMON_SPEED_ONSTAIR;
			vy = -SIMON_SPEED_ONSTAIR;
			
		}
		else {
			vx = -SIMON_SPEED_ONSTAIR;
			vy = SIMON_SPEED_ONSTAIR;
		}*/
		break;
	case  2:
		/*if (nx > 0) {
			vx = SIMON_SPEED_ONSTAIR;
			vy = -SIMON_SPEED_ONSTAIR;

		}
		else {
			vx = -SIMON_SPEED_ONSTAIR;
			vy = SIMON_SPEED_ONSTAIR;
		}*/
		break;
	case 3:

		/*if (nx > 0) {
			vx = SIMON_SPEED_ONSTAIR;
			vy = SIMON_SPEED_ONSTAIR;

		}
		else {
			vx = -SIMON_SPEED_ONSTAIR;
			vy = -SIMON_SPEED_ONSTAIR;
		}*/
		break; 
	case 4:

		//if (nx > 0) {
		//	vx = SIMON_SPEED_ONSTAIR;
		//	vy = SIMON_SPEED_ONSTAIR;

		//}
		//else {
		//	vx = -SIMON_SPEED_ONSTAIR;
		//	vy = -SIMON_SPEED_ONSTAIR;
		//}
		break;
	default:
		break;
	}
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	checkBlink();
	//if(currentStair) {
	//	cout << currentStair->getStairDirection() << endl;
	//}
	if (isBlink) {
		if (GetTickCount() - timeStartBlink >= TIME_BLINK) {
			isBlink = false;
			alpha = 255;
		}
		else {
			alpha = rand() % (255) + 1;
		}
	}
	//Ngăn không cho Simon rớt ra khỏi màn hình
	if (x <= 0) {
		x = 0;
	}
	movingOutStair();
	movingOnStair();
	/*cout << nx << endl;
	cout << vx << endl;*/
	if (isGoToStair) {
		goToStartOnStair();
	}

	//Simon hurt effect 
	if (isHurt) {
		cout << "hurt" << endl;
		if (GetTickCount() - timeStartHurt >= TIME_HURT) {
			vx = 0;
			//SetState(SIMON_STATE_SIT);
			SetState(SIMON_STATE_IDLE);
			isHurt = false;
			//y = y - 70;
			hasGravity = true;
			setFreeze(false);
			cout << "Vo if" << endl;

		}
		else {
				cout << "Vo else" << endl;
				hasGravity = false;
				setFreeze(true);
				if (!isMovingOnStair) {
					vx = -nx * V_HURT;
					vy = -V_HURT;
				}
				SetState(SIMON_STATE_HURT);
		}
	}
	// Simple fall down - Gravity of simon
	if (isThroughBrick) {
		cout << "through all" << endl;
	}
	if (hasGravity) {
		vy += SIMON_GRAVITY * dt;
	}
	
	if (isAutoGoX) {
		vx = nx*SIMON_WALKING_SPEED_AUTO;
		if (nx > 0) {
			if (round(x) >= targetAutoGoX) {
				isAutoGoX = false;
				setFreeze(false);
				isAutoGoXComplete = true; 
				vx = 0;
				cout << "finish right" << endl;
			}
		}
		else {
			if (round(x) <= targetAutoGoX) {
				isAutoGoX = false;
				setFreeze(false);
				isAutoGoXComplete = true;
				vx = 0;
				cout << "finish left" << endl;
			}
		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
 
	coEvents.clear();
	if (isHit) {
		if (GetTickCount()-timeStartHit>=400) {
			isHit = false;
			isHitFinish = true;
			//cout << "Set hit false" << endl;
		}
	}
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (!isTouchable) {
		if (GetTickCount() - timeTouchable > 4000)
		{
			isTouchable = true;
			alpha = 255;
		}
		else {
			alpha = getAlphaRandom();
		}
	}
	

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

		// Collision logic with Object
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CHidden*>(e->obj) && dynamic_cast<CHidden*>(e->obj)->getTypeHidden()==HIDDEN_TYPE_DOOR) {
			/*	isAutoGoX = true;
				x += dx;
				timeStartAutoGoX = GetTickCount();*/
			}
			else if (dynamic_cast<CItem*>(e->obj)) {
				this->colEventWithItem = e;
			}
			else if (dynamic_cast<CBrick*>(e->obj)) {
				if (isMovingOnStair&&isThroughBrick) {
					x += dx;
					y += dy;
					cout << "Through all" << endl;
				}
			}

			
		}
		//Xử lý sau khi nhảy 
		jumpReset();

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
bool CSimon::isCollisionWithItem(CItem* objItem)
{
	if (!objItem->isShow())
		return false;

	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	objItem->GetBoundingBox(l1, t1, r1, b1);
	if (checkAABB(l, t, r, b, l1, t1, r1, b1))
	{
		return true; // check with AABB
	}
	return checkAABBWithObjectAABBEx(objItem);
}

void CSimon::Render()
{
	int ani;
	if (isHit) {
		cout << "hit" << endl;
	}
	switch (state)
	{
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_ON_STAIR:
		switch (typeMovingStair)
		{
		case 1:
			ani = SIMON_ANI_STAIR_UP;
			break;
		case 2:
			ani = SIMON_ANI_STAIR_DOWN;
			break;
		case 3:
			ani = SIMON_ANI_STAIR_ATTACK_UP;
			break;
		case 4:
			ani = SIMON_ANI_STAIR_ATTACK_DOWN;
			break;
		case 5:
			ani = SIMON_ANI_STAIR_IDLE_UP;
			break;
		case 6:
			ani = SIMON_ANI_STAIR_IDLE_DOWN;
			break;
		default:
			break;
		}
		break;
	case SIMON_STATE_SIT:
		if (isHit) {
			//cout << "state sit" << endl;
			ani = SIMON_ANI_SIT_HIT;
		}
		else {
			ani = SIMON_ANI_SIT;
		}
		break;
	case SIMON_STATE_WALKING_BLINK_SINGLE:
		ani = SIMON_ANI_WALKING_BLINK_SINGLE;
		break;
	case SIMON_STATE_JUMP:
		//cout << "state jump" << endl;
		ani = SIMON_ANI_JUMP;
		break;
	case SIMON_STATE_HURT:
		ani = SIMON_ANI_HURT;
		break;
	case SIMON_STATE_HIT:
		ani = SIMON_ANI_HIT;
		if (isSit) {
			ani = SIMON_ANI_SIT_HIT;
		}
		break;
	default:
		
		if (!isJump) {
			
			if (vx == 0)
			{
				if (isHit) {
					ani = SIMON_ANI_HIT;
				}
				else {
					ani = SIMON_ANI_IDLE;
				}
				
			}
			else {
				if (isHit) {
					ani = SIMON_ANI_HIT;
				}
				else {
					ani = SIMON_ANI_WALKING;
				}
			}
		}
		else {
			ani = SIMON_ANI_JUMP;
		}
	break;
	}
	//cout << typeMovingStair << endl;
	CAnimations::GetInstance()->Get(ani)->RenderFlip(-nx,x, y, DEFAULT_OFFSET_X, alpha);
	setCurrentAni(ani);

	if (CGame::GetInstance()->getDebug()) {
		RenderBoundingBox();
	}
}


void CSimon::collisionWithEnemy(vector<LPGAMEOBJECT> listEnemy) {
	for (int i = 0; i < listEnemy.size(); i++) {
		if (checkAABBWithObject(listEnemy[i])&&isTouchable&& listEnemy[i]->isShow()) {
			cout << "va cham" << endl;
				isHurt = true;
				isTouchable = false;
				timeTouchable = GetTickCount();
				timeStartHurt = GetTickCount();
		}
	}
}
void CSimon::goRight() {
	nx = 1;
	if (isMovingOnStair) {
		isGoRight = true;
		
		
		if (currentStairTypeCollision == 1 || currentStairTypeCollision == 2) {
			vx = SIMON_SPEED_ONSTAIR;
			vy = -SIMON_SPEED_ONSTAIR;
			typeMovingStair = 1;
		}
		else {
			vx = SIMON_SPEED_ONSTAIR;
			vy = SIMON_SPEED_ONSTAIR;
			typeMovingStair = 2;
		}
		hasGravity = false;
	}
	if (isGoToStartOnStair) {
		return;
	}
	isGoLeft = false;
	isGoRight = true;
	if (!isJump) {
		nx = 1;
	}
	if (!isJump && !isSit && !isHit) {
		vx = SIMON_WALKING_SPEED;
	}
}

void CSimon::goLeft() {
	nx = -1;
	if (isMovingOnStair) {
		
		hasGravity = false;
		if (currentStairTypeCollision == 1 || currentStairTypeCollision == 2) {
			vx = -SIMON_SPEED_ONSTAIR;
			vy = SIMON_SPEED_ONSTAIR;
			typeMovingStair = 2;
		}
		else {
			vx = -SIMON_SPEED_ONSTAIR;
			vy = -SIMON_SPEED_ONSTAIR;
			typeMovingStair = 1;
		}
	}
	if (isGoToStartOnStair) {
		return;
	}
	isGoLeft = true;
	isGoRight = false;
	if (!isJump) {
		nx = -1;
	}
	if (!isJump && !isSit && !isHit) {
		vx = -SIMON_WALKING_SPEED;
	}
}

void CSimon::goToStartOnStair() {
	int point = 0;
		point = centerPointStair;
	switch (currentStairTypeCollision)
	{
	case 1:
		setFreeze(true);
		if (round(x) < point) {
			nx = 1;
			vx = SIMON_SPEED_ONSTAIR;
		}
		else if (round(x) > point) {
			nx = -1;
			vx = -SIMON_SPEED_ONSTAIR;
		}
		else {
			//vx = 0;
			nx = 1;
			isGoToStair = false;
			isGoToStartOnStair = true;
			hasGravity = false;
			timeToGoToStartOnStair = GetTickCount();
			return;
		}
		break;
	case 2:
		setFreeze(true);
		//vx = 0;
		nx = -1;
		vx = -SIMON_SPEED_ONSTAIR;
		vy = SIMON_SPEED_ONSTAIR;
		isGoToStair = false;
		isGoToStartOnStair = true;
		timeToGoToStartOnStair = GetTickCount();
		break;
	case 3:
		setFreeze(true);
		if (round(x) < point) {
			nx = 1;
			vx = SIMON_SPEED_ONSTAIR;
		}
		else if (round(x) > point) {
			nx = -1;
			vx = -SIMON_SPEED_ONSTAIR;
		}
		else {
			//vx = 0;
			nx = -1;
			isGoToStair = false;
			isGoToStartOnStair = true;
			hasGravity = false;
			timeToGoToStartOnStair = GetTickCount();
			return;
		}
		break;
	case 4:
		setFreeze(true);
		//vx = 0;
		nx = 1;
		vx = SIMON_SPEED_ONSTAIR;
		vy = SIMON_SPEED_ONSTAIR;
		isGoToStair = false;
		isGoToStartOnStair = true;
		timeToGoToStartOnStair = GetTickCount();
		break;
	default:
		break;
	}

}
void CSimon::jump() {
	if (canJump&&!isSit&&!isMovingOnStair) {
		state = SIMON_STATE_JUMP;
		isJump = true;
		canJump = false;
		vy = -SIMON_JUMP_SPEED_Y;
	}
}

void CSimon::jumpReset() {
	
	if (vy <= 0) {
		isJump = false;
	}
	canJump = true;
}
void CSimon::attack() {
	
	if (!this->weapon->getFinish()) {  //Ngan chan khong cho su dung vu khi lien tuc
		return;
	}
	timeStartHit = GetTickCount();
	if (isMovingOnStair) {
		cout << "Set type" << endl;
		typeMovingStair = 3;
	}
	isHit = true;
	this->weapon->attack(x,y,nx);
	this->lastTimeAttack = GetTickCount();
}

void CSimon::attackSub() {

	if (!this->subWeapon->getFinish()) {  //Ngan chan khong cho su dung vu khi lien tuc
		return;
	}
	timeStartHit = GetTickCount();
	this->subWeapon->attack(x, y, nx);
	this->lastTimeAttack = GetTickCount();
}



void CSimon::idle() {
	if (isHit) {
	}
	if (isAutoGoX) {
		return;
	}
	if (isMovingOnStair) {
		if (currentStairTypeCollision == 1 || currentStairTypeCollision == 2)
		{
			
			if (isHit) {
				nx > 0 ? typeMovingStair = 3 : typeMovingStair =4;
			}
			else {
				nx > 0 ? typeMovingStair = 5 : typeMovingStair = 6;
			}
		}
		else {
		
			if (isHit) {
				nx > 0 ? typeMovingStair = 3 : typeMovingStair = 4;
			}
			else {
				nx < 0 ? typeMovingStair = 5 : typeMovingStair = 6;
			}
		}
		return;
	}
	if (isGoToStair) {
		return;
	}
	if (!isJump) {
		vx = 0;
	}
}

void CSimon::die() {
	vy = -SIMON_DIE_DEFLECT_SPEED;
}

void CSimon::sit() {
	if (isGoToStartOnStair) {
		return;
	}
	if (!isJump) {
		isSit = true;
		vx = 0;
	}
}

void CSimon::hit() {
	//cout << "hit hit" << endl;
	isHit = true;
	isHitFinish = false;
	if ((isGoLeft || isGoRight) && !isJump) {
		vx = 0;
	}
	state = SIMON_STATE_HIT;
}

void CSimon::hitRelease() 
{
		//isHit = false;
}

void CSimon::sitRelease() {
	if (isSit) {
		isSit = false;
		y = y - 10;
	}
}

//void CSimon::collisionWithItem(int type) {
	//CWeapon* weapon = CWeapon::GetInstance();
	//switch (type)
	//{
	//case ITEM_TYPE_LARGE_HEART:
	//	cout << "Va cham heart tu simon";
	//	break;
	//case ITEM_TYPE_WHIP_UPGRADE:
	//	timeStartBlink = GetTickCount();
	//	//weapon->setLevel(weapon->getLevel()+1);
	//	setFreeze(true);
	//	setStateBackup(this->state);
	//	SetState(SIMON_STATE_WALKING_BLINK_SINGLE);
	//	break;
	//case ITEM_TYPE_DAGGER:
	//	//weapon->hide();
	//	//weapon->setHasDagger(true);
	//	//weapon->setTypeWeapon(WEAPON_TYPE_NO_WEAPON);
	//	break;
	//default:
	//	break;
	//}
//}

void CSimon::collectDagger() {
	
}
void CSimon::collectWhipUpgrade(CWhip* &whip) {
	timeStartBlink = GetTickCount();
	setFreeze(true);
	SetSpeed(0, 0);
	setStateBackup(this->state);
	SetState(SIMON_STATE_WALKING_BLINK_SINGLE);
	/*whip->setLevel(whip->getLevel() + 1);*/
}
void CSimon::checkBlink() {
	if (getFreeze()) {
		if (GetTickCount() - timeStartBlink >= TIME_BLINK) {
			setFreeze(false);
			SetState(getStateBackup());
		}
	}
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		goRight();
		break;
	case SIMON_STATE_WALKING_LEFT:
		goLeft();
		break;
	case SIMON_STATE_JUMP:
		jump();
		break;
	case SIMON_STATE_IDLE:
		idle();
		break;
	case SIMON_STATE_DIE:
		die();
		break;
	case SIMON_STATE_SIT:
		sit();
		break;
	case SIMON_STATE_SIT_RELEASE:
		sitRelease();
		break;
	case SIMON_STATE_HIT:
		hit();
		break;
	case SIMON_STATE_HIT_RELEASE:
		//cout << "hit release";
		hitRelease();
		break;
	case SIMON_STATE_HURT:
		isHurt = true;
		break;
	}
}

void CSimon::autoGoX(int _nx, float speed,float target)
{
	nx = _nx;
	vx = speed;
	isAutoGoX = true;
	setFreeze(true);
	isAutoGoXComplete = false;
	targetAutoGoX = target;
}

int CSimon::getTypeHiddenCollision(vector<CHidden*> listHidden) {
	for (int i = 0; i < listHidden.size(); i++) {
			if (this->checkAABBWithObjectAABBEx(listHidden[i])) {
				if (listHidden[i]->getTypeHidden() == HIDDEN_TYPE_DOOR) {
				autoGoX(1, SIMON_WALKING_SPEED_AUTO, STAGE_1_TARGET_DOOR);
				isCollisionWithDoor = true;
				return HIDDEN_TYPE_DOOR;
				}
				else if(listHidden[i]->getTypeHidden() == HIDDEN_TYPE_STOP_CREATE_GHOST) {
					return HIDDEN_TYPE_STOP_CREATE_GHOST;
				}
		}
	}
}
CStairPoint* CSimon::checkCollisionStartStair(vector<CStairPoint*> listObj) {
	for (int i = 0; i < listObj.size(); i++) {
		if (this->checkAABBWithObjectAABBEx(listObj[i])) {
			canGoStair = true;
			currentStair = listObj[i];
			centerPointStair = currentStair->getCenter();
			currentStairTypeCollision = currentStair->getStairDirection();
			isThroughBrick = currentStair->getHasThrough();
			return listObj[i];
		}
	}
	canGoStair = false;
}


void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + SIMON_BBOX_MARGIN_LEFT;
	top = y;
	setPositionCustom(left, top);
	
	right = x + SIMON_BBOX_WIDTH ;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isSit) {
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

void CSimon::movingOnStair() {
	if (isGoToStartOnStair) {
		switch (currentStairTypeCollision)
		{
		case 1:
			if (GetTickCount() - timeToGoToStartOnStair >= TIME_AUTO_GO_STAIR) {
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 5;
				vx = 0;  //Set van toc simon dung yen tai thoi diem do
				vy = 0;
				setFreeze(false);
				isMovingOnStair = true;
				hasGravity = false;
			}
			else {
				/*x += nx*0.1;*/
				isMovingOnStair = true;
				state = SIMON_STATE_ON_STAIR;
				typeMovingStair = 1;
				vx = SIMON_SPEED_ONSTAIR;
				vy = -SIMON_SPEED_ONSTAIR;
			}
			break;
		case 2:
			if (GetTickCount() - timeToGoToStartOnStair >= TIME_AUTO_GO_STAIR) {
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 5;
				vx = 0;
				vy = 0;
				setFreeze(false);
				isMovingOnStair = true;
				hasGravity = false;
			}
			else {
				/*x += nx*0.1;*/
				isMovingOnStair = true;
				state = SIMON_STATE_ON_STAIR;
				typeMovingStair = 1;
				vx =-SIMON_SPEED_ONSTAIR;
				vy = SIMON_SPEED_ONSTAIR;
			}
			break;
		case 3:
			if (GetTickCount() - timeToGoToStartOnStair >= TIME_AUTO_GO_STAIR) {
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 5;
				vx = 0;  //Set van toc simon dung yen tai thoi diem do
				vy = 0;
				setFreeze(false);
				isMovingOnStair = true;
				hasGravity = false;
			}
			else {
				/*x += nx*0.1;*/
				isMovingOnStair = true;
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 1;
				vx = -SIMON_SPEED_ONSTAIR;
				vy = -SIMON_SPEED_ONSTAIR;
			}
			break;
		case 4:
			if (GetTickCount() - timeToGoToStartOnStair >= TIME_AUTO_GO_STAIR) {
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 5;
				vx = 0;
				vy = 0;
				setFreeze(false);
				isMovingOnStair = true;
				hasGravity = false;
			}
			else {
				/*x += nx*0.1;*/
				isMovingOnStair = true;
				state = SIMON_STATE_ON_STAIR;
				//typeMovingStair = 2;
				vx = SIMON_SPEED_ONSTAIR;
				vy = SIMON_SPEED_ONSTAIR;
			}
			break;
		default:
			break;
		}
	}
	else {
		//cout << "ONSTAIRFALSE" << endl;
	}
	currentStair = NULL;
}
void CSimon::movingOutStair() {
	if (isMovingOnStair) {
		int directionStair = 0;
		if (currentStair) {
			directionStair = currentStair->getStairDirection();
		}
		switch (directionStair)
		{
		case 1:
			cout << "Out stair" << endl;
			if (nx < 0) {
				isMovingOnStair = false;
				hasGravity = true;
				state = SIMON_STATE_IDLE;
				isGoToStartOnStair = false;
			}
			break;
		case 2:
			cout << "Out stair" << endl;
			if (nx > 0) {
				y = y - 200; // kéo simon lên cao, để tạo va chạm giả xuống mặt đất, tránh overlaping. tính thời gian tiếp đất
				vy = 9999999999.0f; // vận tốc kéo xuống lớn để chạm đất ngay trong 1 frame
				dy = vy * dt; // cập nhật lại dy
				isMovingOnStair = false;
				hasGravity = true;
				//SetState(SIMON_STATE_IDLE);
				state = SIMON_STATE_IDLE;

				isGoToStartOnStair = false;
			}
			break;
		case 3:
			cout << "Out stair 3" << endl;
			if (nx > 0) {
				isMovingOnStair = false;
				hasGravity = true;
				state = SIMON_STATE_IDLE;
				isGoToStartOnStair = false;
			}
			break;
		case 4:
			cout << "Out stair 4" << endl;
			if (nx < 0) {
				y = y - 50; // kéo simon lên cao, để tạo va chạm giả xuống mặt đất, tránh overlaping. tính thời gian tiếp đất
				vy = 9999999999.0f; // vận tốc kéo xuống lớn để chạm đất ngay trong 1 frame
				dy = vy * dt; // cập nhật lại dy
				isMovingOnStair = false;
				hasGravity = true;
				//SetState(SIMON_STATE_IDLE);
				state = SIMON_STATE_IDLE;

				isGoToStartOnStair = false;
			}
			break;
		default:
			break;
		}
	}
}

