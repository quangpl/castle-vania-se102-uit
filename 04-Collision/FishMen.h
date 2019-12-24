#ifndef __FISHMEN_H__
#define __FISHMEN_H__

#include "GameObject.h" 
#include "Brick.h"
#include "Simon.h"
#include "FireBall.h"
#define FISHMEN_SPEED_Y_UP 0.34f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 350px thì rớt xuống

#define FISHMEN_ANI_IDLE 571
#define FISHMEN_ANI_MOVING 572
#define FISHMEN_ANI_ATTACK 574 // ani lúc fishmen attack#define FISHMEN_ANI_IDLE 571
 
#define FISHMEN_STATE_IDLE 0
#define FISHMEN_STATE_MOVING 1
#define FISHMEN_STATE_ATTACK 2

#define FISHMEN_GRAVITY 0.01f
#define FISHMEN_SPEED_X 0.02f

#define FISHMEN_BBOX_WIDTH 18
#define	FISHMEN_BBOX_HEIGHT 30
#define FISHMEN_DX_LIMIT 100 // đi được khoảng 140px thì đổi hướng
#define FISHMEN_DX_ATTACK_LIMIT 100 // đi được khoảng 140px thì đổi hướng

#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700 // thời gian fishmen phải đứng lại chờ trước khi đi tiếp, sau khi attack
#define BREAK_POINT_DIE_Y 170
class CFishMen : public CGameObject
{
private:
	float yInit; // vị trí y lúc khởi tạo
	float xInit;

	bool isActive;

	float xBefore;
	float xAfter;
	float xAccumulationAttack; // quãng đường đã đi tích lũy, để khi đi đủ giới hạn sẽ attack
	DWORD TimeAttack; // thời điểm attack
	bool isRunning;
	CFireBall* weapon;
	bool isAttacking;
	vector<CGameObject*>* listEnemy;
	/* Lưu thành phần ngoài phục vụ xử lí */
	CSimon* simon;
	vector<CWeapon*>* listWeaponOfEnemy;

public:
	CFishMen(float X, float Y, int Direction, CSimon* simon, vector<CGameObject*> * listEnemy);
	virtual ~CFishMen();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render();
	void attack();
};

#endif 




