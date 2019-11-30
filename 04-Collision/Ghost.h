#include "Enemy.h"
#include "SmallCandle.h"
class CGhost : public CEnemy
{
#define GHOST_ANI 5655
#define GHOST_BBOX_WIDTH 20
#define GHOST_BBOX_HEIGHT 28
#define GHOST_SPEED 0.02f;
public:
	CGhost(int direction) : CEnemy() {
		this->AddAnimation(GHOST_ANI);
		nx = direction;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


