#include "GameObject.h" 
#ifndef __FIREBALL_H__
#define __FIREBALL_H__
#define FIREBALL_SPEED 0.21f

#define FIREBALL_ANI 573
#define FIREBALL_BBOX_WIDTH 7
#define FIREBALL_BBOX_HEIGHT 7

class CFireBall : public CGameObject
{
public:
	CFireBall();

	void attack(float x, float y, float nx );
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif
