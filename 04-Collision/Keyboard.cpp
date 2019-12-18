#include "Keyboard.h"
CGame* gameKey = CGame::GetInstance();
CSimon* simonKey = CSimon::GetInstance();


void CSampleKeyHander::OnKeyDown(int KeyCode)   
{
	
	if (simonKey->getFreeze()) {
		return;
	}
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simonKey->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A: // reset
		simonKey->SetState(SIMON_STATE_IDLE);
		simonKey->SetLevel(SIMON_LEVEL);
		simonKey->SetPosition(50.0f, 0.0f);
		simonKey->SetSpeed(0, 0);
		break;
	case DIK_D: // debug mode
		gameKey->setDebug(!gameKey->getDebug());
		break;
	case DIK_UP: // debug mode
		if (simonKey->getCanGoStair()) {
			simonKey->setIsGoToStair(true);
		}
		break;
	case DIK_Z:
		simonKey->attack();
		simonKey->SetState(SIMON_STATE_HIT);
		break;
	case DIK_2:
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(2);
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
		break;
	case DIK_3:
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(3);
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
		simonKey->SetPosition(50, 100);
		break;
	case DIK_4:
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(4);
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
		simonKey->SetPosition(77, 86.5);
		break;
	case DIK_DOWN: // debug mode
		//cout << "Dang nhan down" << endl;
		if (simonKey->getCanGoStair()) {
			//cout << "Set is go true" << endl;
			simonKey->setIsGoToStair(true);
		}
		break;
	case DIK_F1:
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(2);
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
		simonKey->SetPosition(1600, simonKey->GetPositionY());
		break;
	/*case DIK_Z:
		simonKey->attack();
		simonKey->SetState(SIMON_STATE_HIT);
		break;*/
	}

}

void CSampleKeyHander::OnKeyUp(int KeyCode)   //short event
{

	if (simonKey->getFreeze()) {
		return;
	}
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		simonKey->SetState(SIMON_STATE_SIT_RELEASE);
		break;
	case DIK_Z:
		/*simonKey->SetState(SIMON_STATE_HIT_RELEASE);
		weapon->SetState(WEAPON_STATE_NO_WEAPON);*/
		break;
	case DIK_X:
		/*simonKey->SetState(SIMON_STATE_HIT_RELEASE);*/
		break;
	default:
		break;
	}

}


void CSampleKeyHander::KeyState(BYTE* states)   //long event
{
	
	//Khóa phím khi simon đóng băng
	if (simonKey->getFreeze()) {
		return;
	}
	// disable control key when SIMON die 
	if (simonKey->GetState() == SIMON_STATE_DIE) return;
	if (gameKey->IsKeyDown(DIK_RIGHT))
		simonKey->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (gameKey->IsKeyDown(DIK_LEFT))
		simonKey->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simonKey->SetState(SIMON_STATE_IDLE);
	if (gameKey->IsKeyDown(DIK_DOWN))
	{
		if (simonKey->getCanGoStair()) {
			return;
		}
		//cout<<"vuot ngoai" << endl;
		if (simonKey->GetState() == SIMON_STATE_HIT) {
			simonKey->SetState(SIMON_STATE_HIT);
		}
		simonKey->SetState(SIMON_STATE_SIT);
	}

	if (gameKey->IsKeyDown(DIK_Z))
	{
	/*	simonKey->attack();
		simonKey->SetState(SIMON_STATE_HIT);*/
	}
	if (gameKey->IsKeyDown(DIK_X))
	{
		if (simonKey->getSubWeapon()) {
			simonKey->attackSub();
			simonKey->SetState(SIMON_STATE_HIT);
		}
	}
}