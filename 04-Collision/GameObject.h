#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"
#include "Sprites.h"


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

	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	void setPositionCustom(float x, float y) { this->xRender = x, this->yRender = y; }
	void getPositionCustom(float& x, float& y) { x = this->xRender;  y = this->yRender; }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
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

	~CGameObject();
};

