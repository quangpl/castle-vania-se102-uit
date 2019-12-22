#pragma once
#include "Simon.h"
#define ANI_BAT_MAN_IDLE 701
#define ANI_BAT_MAN_FLY 702

#define SCENCE_WITDH 767
#define ANI_ID_BAT_MAN_IDLE 0
#define ANI_ID_BAT_MAN_FLY 1

#define BAT_MAN_ACTIVE_TIME 2000
#define BAT_MAN_ACTIVE_DISTANCE 84

#define BAT_MAN_FLY_DISTANCE_Y 8

#define BAT_MAN_VELOCITY_X 0.07
#define BAT_MAN_VELOCITY_Y 0.07

#define BAT_MAN_WIDTH 48
#define BAT_MAN_HEIGHT 22

#define BAT_MAN_BOUNDARY_START_STAIGHT_LEFT 416
#define BAT_MAN_BOUNDARY_START_STAIGHT_RIGHT 711

#define BOSS_FLY_START_1 1
#define BOSS_FLY_START_2 2
#define BOSS_FLY_CURVE 3
#define BOSS_FLY_STRAIGHT_1 4 // xử lí di chuyển thẳng lần 1
#define BOSS_FLY_STRAIGHT_2 5 // xử lí di chuyển thẳng lần 2
#define BOSS_ATTACK 6 // xử lí di chuyển của boss khi tấn công

#define LOCK_CAM_POSITION_X 654


class CBatMan :public CGameObject
{
	bool isActive;
private:
	int width, height;
	int ani;

	
	float sx, sy; // vị trí simon theo dt

	int status; // trạng thái xử lí 

	bool isBossAttack; // trạng thái tấn công
	bool isBossActive; // kích hoạt boss

	// Vị trí cũ của Boss
	float xBefore;
	float yBefore;

	// Vị trí tiếp theo của Boss
	float xTarget;
	float yTarget;

	/*BezierCurves*/
	bool isUsingCurve; // sử dụng curve

	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	// Lưu lại y theo dt;
	float yLastFrame;

	DWORD startSpawnTime; // thời gian bắt đầu spawn Boss
	DWORD TimeAttacked; // thời gian bắt đầu spawn Boss
	DWORD TimeWaited; // thời gian đã chờ
	bool isWaiting;

public:
	CBatMan();
	void Render();
	void RenderCurrentFrame();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObject);


	float Curve(float n1, float n2);
	int RandomNumber(int a, int b);

	void Start();
	void StartCurves();
	void StartStaight();
	void StartAttack();

	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void GetPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y;
	}

	bool GetIsBoss()
	{
		return true;
	}
};
