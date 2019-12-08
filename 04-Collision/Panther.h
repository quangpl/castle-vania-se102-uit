#ifndef __PANTHER_H__
#define __PANTHER_H__

#define PANTHER_ANI_SITTING 566
#define PANTHER_ANI_RUNNING 567
#define PANTHER_ANI_JUMPING 568

#define PANTHER_ANI_RUNNING_BEGIN 1
#define PANTHER_ANI_RUNNING_END 3

#define PANTHER_STATE_SITTING 0
#define PANTHER_STATE_RUNNINGG 1
#define PANTHER_STATE_JUMPING 2

#define PANTHER_SPEED_RUNNING 0.018f
#define PANTHER_VYJUMP 0.03f
#define PANTHER_VXJUMP 0.02f

#define PANTHER_GRAVITY 0.005f
#define PANTHER_GRAVITY_JUMPING 0.001f

#define PANTHER_DEFAULT_DISTANCE_AUTO_GO_X_DIRECTION_LEFT 177.0f // khoảng cách Panther tự đi khi chạy bên trái
#define PANTHER_DEFAULT_DISTANCE_AUTO_GO_X_DIRECTION_RIGHT PANTHER_DEFAULT_DISTANCE_AUTO_GO_X_DIRECTION_LEFT - 85 // khoảng cách Panther tự đi khi chạy bên phải

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
	bool isStart; // trạng thái bắt đầu
	float xBackup;
	float startJumpPoint;
	float jumpDistance; // khoảng cách cần chạy
	bool isAutoGoX;
	float AutoGoX_Backup_X;
	float distanceAutoGoX;

	CSimon* simon;

public:
	CPanther(float X, float Y, int Direction, float _jumpDistance, CSimon* simon);
	virtual ~CPanther();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	bool GetIsStart();

	void Jump();
	void Run();
};


#endif