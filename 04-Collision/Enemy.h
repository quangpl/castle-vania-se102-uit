#include "GameObject.h"
#include "Weapon.h"
class CEnemy : public CGameObject
{
public:
	CEnemy() : CGameObject() {

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)=0;
	virtual void Render()=0;
};



