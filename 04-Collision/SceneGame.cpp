﻿#include "SceneGame.h"

CGame* game;
CCandles* candles = CCandles::GetInstance();
CItems* items = CItems::GetInstance();
CWeapon* weapon = CWeapon::GetInstance();
CSimon* simon = CSimon::GetInstance();
Map* map1;

vector<CGameObject*> objects;
CSceneGame* CSceneGame::__instance = NULL;


//class CSampleKeyHander : public CKeyEventHandler
//{
//	virtual void KeyState(BYTE* states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander* keyHandler;
//
//void CSampleKeyHander::OnKeyDown(int KeyCode)   //short event
//{
//	CGame* game;
//	CCandles* candles = CCandles::GetInstance();
//	CItems* items = CItems::GetInstance();
//	CWeapon* weapon = CWeapon::GetInstance();
//	CSimon* simon = CSimon::GetInstance();
//	if (simon->getFreeze()) {
//		return;
//	}
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		simon->SetState(SIMON_STATE_JUMP);
//		break;
//	case DIK_A: // reset
//		simon->SetState(SIMON_STATE_IDLE);
//		simon->SetLevel(SIMON_LEVEL);
//		simon->SetPosition(50.0f, 0.0f);
//		simon->SetSpeed(0, 0);
//		break;
//	}
//
//}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode)   //short event
//{
//	CGame* game;
//	CCandles* candles = CCandles::GetInstance();
//	CItems* items = CItems::GetInstance();
//	CWeapon* weapon = CWeapon::GetInstance();
//	CSimon* simon = CSimon::GetInstance();
//	if (simon->getFreeze()) {
//		return;
//	}
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_DOWN:
//		simon->SetState(SIMON_STATE_SIT_RELEASE);
//		break;
//	case DIK_Z:
//		simon->SetState(SIMON_STATE_HIT_RELEASE);
//		//weapon->SetState(WEAPON_STATE_NO_WEAPON);
//		break;
//	case DIK_X:
//		simon->SetState(SIMON_STATE_HIT_RELEASE);
//		break;
//	default:
//		break;
//	}
//
//}
//
//
//void CSampleKeyHander::KeyState(BYTE* states)   //long event
//{
//	CGame* game = CGame::GetInstance();
//	CCandles* candles = CCandles::GetInstance();
//	CItems* items = CItems::GetInstance();
//	CWeapon* weapon = CWeapon::GetInstance();
//	CSimon* simon = CSimon::GetInstance();
//	//Khóa phím khi simon đóng băng
//	if (simon->getFreeze()) {
//		return;
//	}
//	// disable control key when SIMON die 
//	if (simon->GetState() == SIMON_STATE_DIE) return;
//	if (game->IsKeyDown(DIK_RIGHT))
//		simon->SetState(SIMON_STATE_WALKING_RIGHT);
//	else if (game->IsKeyDown(DIK_LEFT))
//		simon->SetState(SIMON_STATE_WALKING_LEFT);
//	else
//		simon->SetState(SIMON_STATE_IDLE);
//	if (game->IsKeyDown(DIK_DOWN))
//	{
//		if (simon->GetState() == SIMON_STATE_HIT) {
//			weapon->SetState(WEAPON_STATE_ROPE);
//			simon->SetState(SIMON_STATE_HIT);
//		}
//		simon->SetState(SIMON_STATE_SIT);
//	}
//
//	if (game->IsKeyDown(DIK_Z))
//	{
//		weapon->SetState(WEAPON_STATE_ROPE);
//		simon->SetState(SIMON_STATE_HIT);
//	}
//	if (game->IsKeyDown(DIK_X) && weapon->getHasDagger() && !weapon->isShow())
//	{
//		//weapon->show();
//		weapon->setTypeWeapon(WEAPON_TYPE_DAGGER);
//		weapon->SetState(WEAPON_STATE_DAGGER);
//		simon->SetState(SIMON_STATE_HIT);
//	}
//}

CSceneGame::CSceneGame()
{
	setStage(1);
}

CSceneGame::~CSceneGame()
{
}

CSceneGame* CSceneGame::GetInstance()
{
	if (__instance == NULL) __instance = new CSceneGame();
	return __instance;
}

void CSceneGame::LoadResources() {
		CTextures * textures = CTextures::GetInstance();

		textures->Add(ID_TEX_MAP, "textures\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
		textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV3.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));




		map1 = new Map(ID_TEX_MAP, "textures\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
		map1->ReadMapTXT("textures\\Map1.txt");
		map1->LoadTile();

		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();

		LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
		LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);

		//Load tất cả animations
		LPDIRECT3DTEXTURE9 directTexture;
		TiXmlDocument doc("XML/Textures.xml");
		if (!doc.LoadFile())
		{
			DebugOut(L"Can't read XML file");
			MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
			return;
		}
		else
		{
			DebugOut(L"[INFO]Read XML success\n");
		}
		// get info root
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* sprite = nullptr;
		TiXmlElement* animation = nullptr;
		TiXmlElement* texture = nullptr;
		LPANIMATION ani;
		int nItem = 1;
		// gameObjectId = 0 -- Simon
		for (texture = root->FirstChildElement(); texture != NULL; texture = texture->NextSiblingElement())
		{
			int textureId;
			int gameObjectId;
			texture->QueryIntAttribute("textureId", &textureId);
			texture->QueryIntAttribute("gameObjectId", &gameObjectId);

			directTexture = textures->Get(textureId);
			for (animation = texture->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
			{
				int aniId, frameTime;
				animation->QueryIntAttribute("frameTime", &frameTime);

				ani = new CAnimation(frameTime);
				for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
				{
					int left, top, right, bottom, id;
					sprite->QueryIntAttribute("id", &id);
					sprite->QueryIntAttribute("top", &top);
					sprite->QueryIntAttribute("left", &left);
					sprite->QueryIntAttribute("right", &right);
					sprite->QueryIntAttribute("bottom", &bottom);
					sprites->Add(id, left, top, right, bottom, directTexture);
					ani->Add(id);
				}
				animation->QueryIntAttribute("aniId", &aniId);
				animations->Add(aniId, ani);
				if (gameObjectId == 0)
				{
					simon->AddAnimation(aniId);
				}
				else if (gameObjectId == 100) {
					weapon->AddAnimation(aniId);
				}
				else if (gameObjectId == 2) {
					CItem* item = new CItem();
					item->AddAnimation(aniId);
					item->SetState(ITEM_STATE_HIDE);
					objects.push_back(item);
					items->Add(nItem, item);
					nItem++;
				}
				else if (gameObjectId == 21) {
					for (int i = 1; i <= NUMBER_OF_CANDLE; i++) {
						CCandle* candle = new CCandle();
						candle->AddAnimation(aniId);
						candle->SetState(CANDLE_STATE_SHOW);
						candle->SetPosition(i * DISTANCE_BETWEEN_CANDLE, Y_BASE);
						candle->setId(i);
						candles->Add(candle);
						objects.push_back(candle);
					}
				}
				else if (gameObjectId == 28) {

					for (int i = 0; i < NUMBER_OF_BRICK; i++)
					{
						float l, t, r, b;
						CBrick* brick = new CBrick();
						brick->AddAnimation(aniId);
						brick->SetPosition(0 + i * 16.0f, SCREEN_HEIGHT - 45);
						objects.push_back(brick);
					}
				}
			};


		}


		simon->SetPosition(50.0f, 0); //simon
		objects.push_back(simon);


		weapon->SetPosition(50.0f, 0);
		weapon->setLevel(1);
		weapon->setTypeWeapon(WEAPON_TYPE_NO_WEAPON);
		objects.push_back(weapon);
}

void CSceneGame::Update(DWORD dt) {
	float xWeapon, yWeapon;
	weapon->GetPosition(xWeapon, yWeapon);
	if (xWeapon <= 0 || xWeapon >= map1->getMapWidth()) {
		weapon->hide();
	}

	vector<LPGAMEOBJECT> coPlayerAndBackground;
	vector<LPGAMEOBJECT> coWeaponAndCandle;
	vector<LPGAMEOBJECT> coEffects;




	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isShow()) {
			if (dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				coPlayerAndBackground.push_back(objects[i]);
			}

			if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])) {
				coWeaponAndCandle.push_back(objects[i]);
			}
		}
		/*else {
			if (dynamic_cast<CCandle*>(objects[i])) {
				CEffects* effects = new CEffects();
				effects->setTimeStartAppear(GetTickCount());
				float x, y;
				objects[i]->GetPosition(x, y);
				effects->SetPosition(x, y);
				coEffects.push_back(effects);
				objects.push_back(effects);
			}
		}*/
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
			objects[i]->Update(dt, &coPlayerAndBackground);
		}

		if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])) {
			objects[i]->Update(dt, &coWeaponAndCandle);
		}
	}


	// Update camera to follow SIMON
	float cx, cy, camX, camY;
	simon->GetPosition(cx, cy);

	camX = CGame::GetInstance()->GetCamPos_x();
	camY = CGame::GetInstance()->GetCamPos_y();
	//Khoảng cách để Simon vô giữa màn hình
	if (cx >= SCREEN_WIDTH / 2) {
		cx -= SCREEN_WIDTH / 2;
	}
	else {
		cx = 0;
	}
	CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 

	if (camX + SCREEN_WIDTH >= map1->getMapWidth() && cx >= map1->getMapWidth() - SCREEN_WIDTH) {
		CGame::GetInstance()->SetCamPos(camX, CAM_Y_DEFAULT);
	}
}
void CSceneGame::Render() {
	map1->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void CSceneGame::Init(HWND hWnd) {
	//game->Init(hWnd);
	//CSampleKeyHander* keyHandler = new CSampleKeyHander();
	//game->InitKeyboard(keyHandler);
}