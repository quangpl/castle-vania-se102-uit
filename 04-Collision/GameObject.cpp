#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	health = 1;
}

bool CGameObject::checkAABB(float left_a, float top_a, float right_a, float bottom_a, float left_b, float top_b, float right_b, float bottom_b)
{
	return left_a < right_b && right_a > left_b && top_a < bottom_b && bottom_a > top_b;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

bool CGameObject::checkAABBWithObject(CGameObject *obj)
{
		float l, t, r, b;
		float l1, t1, r1, b1;
		this->GetBoundingBox(l, t, r, b);
		obj->GetBoundingBox(l1, t1, r1, b1);

		if (this->checkAABB(l, t, r, b, l1, t1, r1, b1))
		{
			return true;
		}
		return false;
}
bool CGameObject::checkAABBWithObjectAABBEx(CGameObject* obj) {
		if (checkAABBWithObject(obj)) // kiểm tra va chạm bằng AABB trước
			return true;

		LPCOLLISIONEVENT e = SweptAABBEx(obj); // kt va chạm giữa 2 object bằng sweptAABB
		bool res = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
		return res;
}
void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	if (xRender == 999999 && yRender == 999999) {
		CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 128);
	}
	else {
		CGame::GetInstance()->Draw(xRender, yRender, bbox, rect.left, rect.top, rect.right, rect.bottom, 128);
	}
	
}
	

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

int CGameObject::getAlphaRandom() {
	int a = 0,b=255;
	return a + rand() % (b - a + 1);
}

bool CGameObject::isInCamera(float width, float height ) {
	float x = this->GetPositionX();
	float y = this->GetPositionY();
	float xCam = CGame::GetInstance()->GetCamPos_x();
	float yCam = CGame::GetInstance()->GetCamPos_y();
	if (x + width < xCam || xCam + SCREEN_WIDTH < x)
		return false;
	if (y + height < yCam || yCam + SCREEN_HEIGHT < y)
		return false;
	return true;
}

CGameObject::~CGameObject()
{

}