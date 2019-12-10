#pragma once
#include "Splash.h"

CSplash::CSplash(float x, float y) : CEffect(x,y)
{
	this->AddAnimation(ANI_SPLASH);
	timeCreate = GetTickCount();
	int random = rand() % 2;
	if (random == 1)
	{
		this->x = x - SPLASH_OFFSET_X;
		this->vx = -SPLASH_VELOCITY_X;
	}
	else if (random == 2)
	{
		this->x = x - SPLASH_OFFSET_X;
		this->vx = -SPLASH_VELOCITY_X;
	}
	else
	{
		this->vx = 0;
		this->x = x + SPLASH_OFFSET_X;
	}

	this->y = y;
	this->vy = -SPLASH_VELOCITY_y;
}

void CSplash::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += SPLASH_GRAVITY * dt;

	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;
}

void CSplash::Render() {
		animations[ANI_SPLASH_ID]->Render(x, y);
}

void CSplash::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	r = y;
	r = x + 20;
	b = y + 20;
}
