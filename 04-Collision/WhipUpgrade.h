#ifndef __WHIPUPGRADE_H__
#define	__WHIPUPGRADE_H__
#pragma once
#include "Items.h"

#define WHIP_UPGRADE_BBOX_WIDTH 22
#define WHIP_UPGRADE_BBOX_HEIGHT 16

#define ITEM_ANI_WHIP_UPGRADE 540
class CWhipUpgrade : public CItem
{
public:
	CWhipUpgrade(float x, float y) : CItem(x, y) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

#endif
