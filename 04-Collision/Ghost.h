#pragma once
#include "Brick.h"
#include "GameObject.h"

#define GHOST_BBOX_WIDTH 18
#define GHOST_BBOX_HEIGHT 30

#define GHOST_SPEED 0.02f
#define GHOST_FALLDOWN_SPEED 0.002f
#define GHOST_ANI 5655
class CGhost : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CGhost(float _x,float _y, int direction):CGameObject(){
		x = _x;
		y = _y;
		nx = direction;
		setType(TYPE_OBJECT_ENEMY);
	};
};
