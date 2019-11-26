#include "SceneGame.h"

CGame* game;
//CCandles* candles = CCandles::GetInstance();
CSimon* simon = CSimon::GetInstance();
CMaps* maps = CMaps::GetInstance();
CWhip* whip;
CSceneGame* CSceneGame::__instance = NULL;
vector<CItem*> listItem;

CSceneGame::CSceneGame()
{
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
	cout << "load res" << endl;
	if (getStage() == 1) {
		objects.clear();
		CTextures* textures = CTextures::GetInstance();

		textures->Add(ID_TEX_MAP_1, "Map\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
		textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV3.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));




		CMap* map = new CMap(ID_TEX_MAP_1, "Map\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
		map->ReadMapTXT("Map\\Map1.txt");
		map->LoadTile();

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
					whip = new CWhip();
					whip->AddAnimation(aniId);
					whip->setLevel(1);
				}
				/*else if (gameObjectId == 2) {
					CItem* item = new CItem();
					item->AddAnimation(aniId);
					item->SetState(ITEM_STATE_HIDE);
					objects.push_back(item);
					items->Add(nItem, item);
					nItem++;
				}*/
				else if (gameObjectId == 21) {
					for (int i = 1; i <= NUMBER_OF_CANDLE; i++) {
						CCandle* candle = new CCandle();
						candle->AddAnimation(aniId);
						candle->SetState(CANDLE_STATE_SHOW);
						candle->SetPosition(i * DISTANCE_BETWEEN_CANDLE, Y_BASE);
						candle->setId(i);
						//candles->Add(candle);
						objects.push_back(candle);
					}
				}
				else if (gameObjectId == 28) {
					for (int i = 0; i < NUMBER_OF_BRICK; i++)
					{
						float l, t, r, b;
						CBrick* brick = new CBrick();
						brick->AddAnimation(aniId);
						brick->SetPosition(0 + i * 16.0f, SCREEN_HEIGHT - 45); //Anhr huong vi tri simon
						objects.push_back(brick);
					}
				}
			};


		}

		CHidden* hidden = new CHidden(10, 80,HIDDEN_TYPE_DOOR);
		hidden->SetPosition(685,130);
		objects.push_back(hidden);

		simon->SetPosition(50.0f, 0); //simon
		simon->setWeapon(whip);
		objects.push_back(simon);


		objects.push_back(whip);
		maps->Add(ID_MAP_1, map);
		currentIdMap = ID_MAP_1;
	}
	else if (getStage() == 2) {
		{
			objects.clear();
			CTextures* textures = CTextures::GetInstance();

			textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_SIMON, "textures\\TexturesV3.png", D3DCOLOR_XRGB(34, 177, 76));
			textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
			textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));




			CMap* map = new CMap(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
			map->ReadMapTXT("Map\\Map2.txt");
			map->LoadTile();

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
						whip = new CWhip();
						whip->setLevel(1);
						whip->AddAnimation(aniId);
					}
					else if (gameObjectId == 28) {
						for (int i = 0; i < NUMBER_OF_BRICK; i++)
						{
							float l, t, r, b;
							CBrick* brick = new CBrick();
							brick->AddAnimation(aniId);
							brick->SetPosition(0 + i * 16.0f, SCREEN_HEIGHT - 30);
							objects.push_back(brick);
						}
					}
				};


			}
			simon->stopAutoGoX();
			simon->SetPosition(50.0f, 0); //simon
			objects.push_back(simon);


			objects.push_back(whip);
			maps->Add(ID_MAP_2, map);
			currentIdMap = ID_MAP_2;
		}
}
	else {
			cout << "CANNOT SET STAGE or STAGE NULL" << endl;
	}
	//isUpdateScene = true;
}
void CSceneGame::checkUpdateScene() {
	switch (getStage())
	{
	case 1:
		if (simon->getIsCollisionWithDoor()) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(2);
			LoadResources();
		}
		break;
	default:
		break;
	}
}
void CSceneGame::Update(DWORD dt) {
	/*float xWeapon, yWeapon;
	weapon->GetPosition(xWeapon, yWeapon);
	if (xWeapon <= 0 || xWeapon >= maps->Get(ID_MAP_1)->getMapWidth()) {
		weapon->hide();
	}*/
	//cout << simon->GetPositionX() << endl;
	checkUpdateScene();
	/*if (dynamic_cast<CWeapon*>(whip)) {
		cout << "OK laf weapon" << endl;
	}*/
	whip->SetPosition(simon->GetPositionX(), simon->GetPositionY());
	vector<LPGAMEOBJECT> coPlayerAndBackground;
	vector<LPGAMEOBJECT> coWeaponAndCandle;
	vector<LPGAMEOBJECT> coEffects;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getHealth()>0) {
			
			if (dynamic_cast<CHidden*>(objects[i]) || dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				coPlayerAndBackground.push_back(objects[i]);
			}

			if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])) {
				coWeaponAndCandle.push_back(objects[i]);
			}
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getHealth() > 0) {

			if (dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				objects[i]->Update(dt, &coPlayerAndBackground);
			}

			if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])) {
				objects[i]->Update(dt, &coWeaponAndCandle);
			}
		}
	}
	//Check collision area
	checkCollisonOfWeapon(coWeaponAndCandle);
	checkCollisionSimonWithItem();

	// Update camera to follow SIMON
	float cx, cy, camX, camY;
	simon->GetPosition(cx, cy);

	camX = CGame::GetInstance()->GetCamPos_x();
	camY = CGame::GetInstance()->GetCamPos_y();
	//Khoảng cách để Simon vô giữa màn hình

	//CGame::GetInstance()->SetCamPos(cx, 23.0f);
	if (cx >= SCREEN_WIDTH / 2) {
		cx -= SCREEN_WIDTH / 2;
	}
	else {
		cx = 0;
	}
	if (getStage() == 1) {
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT_STAGE_1); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch
		if (camX + SCREEN_WIDTH >= maps->Get(ID_MAP_1)->getMapWidth() && cx >= maps->Get(ID_MAP_1)->getMapWidth() - SCREEN_WIDTH) {
			CGame::GetInstance()->SetCamPos(camX, CAM_Y_DEFAULT_STAGE_1);
		}
	}
	else if (getStage() == 2) {
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT_STAGE_2); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 
		if (camX + SCREEN_WIDTH >= maps->Get(ID_MAP_2)->getMapWidth() && cx >= maps->Get(ID_MAP_2)->getMapWidth() - SCREEN_WIDTH) {
			CGame::GetInstance()->SetCamPos(camX, CAM_Y_DEFAULT_STAGE_2);
		}
	}

}
void CSceneGame::Render() {
	maps->Get(currentIdMap)->Render();
	for (int i = 0; i < objects.size(); i++)
	{
			objects[i]->Render();
	}
}
//void CSceneGame::checkCollisonOfSimon() {
//	LPCOLLISIONEVENT colEventWithItem = simon->getCollisionEventWithItem();
//	if (colEventWithItem) {
//		if ((dynamic_cast<CLargeHeart*>(colEventWithItem->obj))) {
//			cout << "An tim" << endl;
//			colEventWithItem->obj->hide();
//		}
//		else if ((dynamic_cast<CWhipUpgrade*>(colEventWithItem->obj))) {
//			simon->collectWhipUpgrade(whip);
//		}
//		if ((dynamic_cast<CDaggerItem*>(colEventWithItem->obj))) {
//			colEventWithItem->obj->subHealth(-1);
//		}
//	}
//}

void CSceneGame::checkCollisionSimonWithItem() {
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CItem*>(objects[i])) {
			if (simon->isCollisionWithItem(dynamic_cast<CItem*>(objects[i]))) {
				cout << "va cham item ne" << endl;
				deleteObject(objects,i);
				getBonusFromItem(dynamic_cast<CItem*>(objects[i]));
			}
		}
	}
}
void CSceneGame::checkCollisonOfWeapon(vector<LPGAMEOBJECT> &listObjects) {
	CWeapon* weapon = simon->getWeapon();
	if (weapon->getFinish()&&simon->getIsHit()) { //Vu khi dang hoat dong moi xet va cham
		for (int i = 0; i < listObjects.size(); i++) {
			if (dynamic_cast<CCandle*>(listObjects[i]) && weapon->checkAABBWithObject(listObjects[i])) {
				objects.push_back(getItem(dynamic_cast<CCandle*>(listObjects[i])->getId(), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
				//cout << objects[i]->getHealth() << endl;
				objects[i]->subHealth(1);
				deleteObject(objects, i);
				return;
			}
		}
	}
}
void CSceneGame::getBonusFromItem(CItem* item) {
	if (dynamic_cast<CLargeHeart*>(item)) {
		cout << "Dang dung vao heart" << endl;
	}
	else if(dynamic_cast<CWhipUpgrade*>(item)) {
		cout << "Dang dung vao upgrade" << endl;
		//simon->collectWhipUpgrade(whip);
	}
	else if (dynamic_cast<CDaggerItem*>(item)) {
		cout << "Dang dung vao upgrade" << endl;
	}
}
CItem* CSceneGame::getItem(int id, float x, float y) {
	switch (id)
	{
	case 1:
		return new CLargeHeart(x,y);
		break;
	case 2:
		return new CWhipUpgrade(x, y);
		break;
	case 3:
		return new CWhipUpgrade(x, y);
		break;
	case 4:
		return new CLargeHeart(x, y);
		break;
	case 5:
		return new CDaggerItem(x, y);
		break;
	default:
		break;
	}
}
void CSceneGame::deleteObject(vector<LPGAMEOBJECT> &listObj, int index) {
	listObj.erase(listObj.begin() + index);
}




