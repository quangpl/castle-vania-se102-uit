#ifndef __WHIPUPGRADE_H__
#define	__WHIPUPGRADE_H__
#pragma once
#include "Items.h"
class CWhipUpgrade : public CItem
{
public:
	CWhipUpgrade() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

#endif
