#ifndef __FISHMEN_H__
#define __FISHMEN_H__

#include "GameObject.h" 
#include "Brick.h"
#include "Simon.h"
#include "FireBall.h"
#define FISHMEN_SPEED_Y_UP 0.4f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 450px thì rớt xuống

#define FISHMEN_ANI_IDLE 571
#define FISHMEN_ANI_MOVING 572
#define FISHMEN_ANI_ATTACK 573 // ani lúc fishmen attack
#define FISHMEN_ANI_JUMP 2 // ani lúc nhảy
#define FISHMEN_ANI_WALK_BEGIN 1 // ani bắt đầu đi
#define FISHMEN_ANI_WALK_END 2 


#define FISHMEN_GRAVITY 0.01f
#define FISHMEN_SPEED_X 0.02f

#define FISHMEN_BBOX_WIDTH 20
#define	FISHMEN_BBOX_HEIGHT 32
#define FISHMEN_DX_LIMIT 100 // đi được khoảng 140px thì đổi hướng
#define FISHMEN_DX_ATTACK_LIMIT 100 // đi được khoảng 140px thì đổi hướng

#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700 // thời gian fishmen phải đứng lại chờ trước khi đi tiếp, sau khi attack
#define BREAK_POINT_DIE_Y 170
class CFishMen : public CGameObject
{
private:
	float yInit; // vị trí y lúc khởi tạo
	float xInit;

	float xBefore;
	float xAfter;
	float xAccumulationAttack; // quãng đường đã đi tích lũy, để khi đi đủ giới hạn sẽ attack
	DWORD TimeAttack; // thời điểm attack
	bool isRunning;
	//FireBall* weapon;
	bool isAttacking;

	/* Lưu thành phần ngoài phục vụ xử lí */
	CSimon* simon;
	vector<CWeapon*>* listWeaponOfEnemy;

public:
	CFishMen(float X, float Y, int Direction, CSimon* simon);
	virtual ~CFishMen();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render();
	void attack();
};

#endif 




