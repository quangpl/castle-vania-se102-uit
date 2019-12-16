#ifndef __PANTHER_H__
#define __PANTHER_H__

#define PANTHER_ANI_SITTING 566
#define PANTHER_ANI_RUNNING 567
#define PANTHER_ANI_JUMPING 568

#define PANTHER_STATE_SITTING 0
#define PANTHER_STATE_RUNNING 1
#define PANTHER_STATE_JUMPING 2


#define PANTHER_SPEED_RUNNING 0.08f
#define PANTHER_VY_JUMP 0.06f
#define PANTHER_VX_JUMP 0.1f

#define PANTHER_GRAVITY 0.01f


#define PANTHER_BBOX_WIDTH 32
#define PANTHER_BBOX_HEIGHT 16

#include "Simon.h"
#include "Brick.h"

class CPanther : public CGameObject
{
private:
	bool isSitting;
	bool isRunning;
	bool isJumping;
	CSimon* simon;
	bool isLanding;
	bool hasStart;
public:
	CPanther(float X, float Y, int Direction, CSimon* simon);
	virtual ~CPanther();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};


#endif