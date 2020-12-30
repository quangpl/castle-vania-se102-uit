#ifndef __BAT_H__
#define __BAT_H__

#include "GameObject.h" 
#include <iostream>
#define BAT_SPEED_X 0.08f 
#define BAT_SPEED_Y 0.08f

#define DeltaY 20 
#define BAT_ANI 570
#define BAT_BBOX_WIDTH 20
#define BAT_BBOX_HEIGHT 20

class CBat : public CGameObject
{
private:
	float yBackup; // vị trí của y ban dầu

public:
	CBat(float X = 0, float Y = 0, int Direction = -1);
	virtual ~CBat();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

#endif