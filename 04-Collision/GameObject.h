﻿#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"
#include "Sprites.h"
#include "Game.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define RENDER_POSITION_TEMP 999999.0f;
class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:


	bool isActive; //de check doi tuong da hoat dong trong camera
	float x; 
	float y;

	float xRender = RENDER_POSITION_TEMP;
	float yRender = RENDER_POSITION_TEMP;

	bool isShowState = true; //Trạng thái ẩn /hiện của đối tượng
	bool isFreeze = false; //Mặc định gameObject sẽ không bị đóng băng

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;
	int stateBackup;

	int currentAni;

	DWORD dt; 
	int typeObject;   

	int health; //Object nao cung co suc khoe ban dau la 1
	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	RECT GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}
	void setPositionCustom(float x, float y) { this->xRender = x, this->yRender = y; }
	void getPositionCustom(float& x, float& y) { x = this->xRender;  y = this->yRender; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	float getVx() { return this->vx; };
	float getVy() { return this->vy; };
	void setVx(float _vx) { this->vx = _vx; }
	void setVy(float _vy) { this->vy = _vy; }

	int getDirection() { return this->nx; };

	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	float GetPositionX() { return this->x; };
	float GetPositionY() { return this->y; };
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }
	int getType() { return this->typeObject; };
	void setType(int type) { this->typeObject = type; };
	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();
	bool checkAABB(float left_a, float top_a, float right_a, float bottom_a, float left_b, float top_b, float right_b, float bottom_b);
	bool checkAABBWithObject(CGameObject* obj);
	bool checkAABBWithObjectAABBEx(CGameObject* obj);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	void setFreeze(bool isFree) { this->isFreeze = isFree; };
	bool getFreeze() { return this->isFreeze; };

	void show() { isShowState = true; };
	void hide() { isShowState = false; };
	bool isShow() { return this->isShowState; };
	

	void setStateBackup(int state) { this->stateBackup = state; };
	int getStateBackup() { return this->stateBackup; };

	void setCurrentAni(int ani) { this->currentAni = ani; };
	int getCurrentAni() { return this->currentAni; };

	bool isInCamera(float w,float h); // Kiem tra object co nam trong camera hay khong

	int getHealth() { return health; };
	void setHealth(int h) { health = h; };
	void updateHealth(int h) { this->health = this->health + h; };
	void subHealth(int h) { health = health - h;
	if (health < 0) {
		health = 0;
	}
	};
	int getAlphaRandom();
	bool isInCamera(float x, float y, float w, float h);
	~CGameObject();
};

