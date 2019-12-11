#include "SceneGame.h"

CGame* game = CGame::GetInstance();
//CCandles* candles = CCandles::GetInstance();
CSimon* simon = CSimon::GetInstance();
CMaps* maps = CMaps::GetInstance();
CWhip* whip;
CWeapon* backupWeapon;
CWeapon* backupSubWeapon;
CSceneGame* CSceneGame::__instance = NULL;
vector<CItem*> listItem;
vector<CEffect*> listEffect;
vector<CHidden*> listHidden;
vector<CGameObject*> listBrick;
vector<CStairPoint*> listStairPoint;
vector<CDoor*> listDoor;
vector<CGameObject*> listEnemy;
CDoor* currentDoor;

CSceneGame::CSceneGame()
{
	isWaitSimonThroughScene = false;
	isStageMoving = false;
	isProcessStageChange = false;

	isAllowToCreateGhost = false;
	isWaitingToCreateGhost = false;
	
	isAllowToCreatePanther = false;

	isAllowCreateBat = false;
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
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));
		textures->Add(ID_TEX_ENEMY, "textures\\enemy.png", D3DCOLOR_XRGB(96, 68, 106));




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
				else if (gameObjectId == 211) {
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
				else if (gameObjectId == 282) {
					for (int i = 0; i < NUMBER_OF_BRICK; i++)
					{
						float l, t, r, b;
						CBrick* brick = new CBrick();
						brick->SetPosition(0 + i * 16.0f, SCREEN_HEIGHT - 45); //Anhr huong vi tri simon
						objects.push_back(brick);
						listBrick.push_back(brick);
					}
				}
			};
		}
		

		
		CHidden* hidden = new CHidden(685,130,10, 80, HIDDEN_TYPE_DOOR);
		listHidden.push_back(hidden);

		simon->SetPosition(50.0f, 0); //simon
		simon->setWeapon(whip);
		objects.push_back(simon);

		/*CFishMen* fish = new CFishMen(100, 100, 1, simon);
		objects.push_back(fish);
		listEnemy.push_back(fish);*/

	/*	CGhost* newGhost3 = new CGhost(30, 50, -1);
		objects.push_back(newGhost3);
		listEnemy.push_back(newGhost3);


		CGhost* newGhost = new CGhost(100,50,1);
		objects.push_back(newGhost);
		listEnemy.push_back(newGhost);

		CGhost* newGhost2 = new CGhost(150, 50, 1);

		objects.push_back(newGhost2);
		listEnemy.push_back(newGhost2);*/

		objects.push_back(whip);
		maps->Add(ID_MAP_1, map);
		currentIdMap = ID_MAP_1;


	}
	else if (getStage() == 2) 
		{
		cout << "load stage 2" << endl;
			//objects.clear();
			objects.clear();
			listHidden.clear();
			listStairPoint.clear();
			listDoor.clear();
			listBrick.clear();

			//config init constant
			isAllowToCreateGhost = true;
			
			listHidden.clear();
			CTextures* textures = CTextures::GetInstance();

			textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
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
				};


			}

			//Load new object
			TiXmlDocument Map2Object("XML/Map2_Objects.xml");
			if (!Map2Object.LoadFile())
			{
				DebugOut(L"Can't read XML file: %s");
				MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
				return;
			}
			// get info root
			 root = Map2Object.RootElement();
			TiXmlElement* Objects = nullptr;
			TiXmlElement* Object = nullptr;
			for (Objects = root->FirstChildElement(); Objects != NULL; Objects = Objects->NextSiblingElement())
			{
				int id;
				float x, y, Width, Height,direction,center;
				float isThroughBrick;
				Objects->QueryIntAttribute("id", &id);
				for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
				{
					Object->QueryFloatAttribute("x", &x);
					Object->QueryFloatAttribute("y", &y);
					Object->QueryFloatAttribute("width", &Width);
					Object->QueryFloatAttribute("height", &Height);
					Object->QueryFloatAttribute("direction", &direction);
					Object->QueryFloatAttribute("center", &center);
					Object->QueryFloatAttribute("isThroughBrick", &isThroughBrick);

					if (id == 0)
					{
						CBrick* newBrick = new CBrick();
						newBrick->setSize(Width, Height);
						newBrick->SetPosition(x, y);
						listBrick.push_back(newBrick);
						objects.push_back(newBrick);
					}
					
					 if (id == 2) {
						CSmallCandle* smallCandle = new CSmallCandle();
						smallCandle->SetPosition(x, y);
						objects.push_back(smallCandle);
					}
					else if (id == -1) {
						CDoor* door = new CDoor(x, y,2); //2: id stage 2 , stage cua cua dang dung
						door->SetState(DOOR_STATE_STATIC);
						objects.push_back(door);
						listDoor.push_back(door);
					}
					else if (id == -3)
					{
						CStairPoint* stairPoint = new CStairPoint(x,y, Width, Height, direction);
						stairPoint->setCenter(center);
						stairPoint->setCenter(center);
						stairPoint->setHasThrough(isThroughBrick);
						objects.push_back(stairPoint);
						listStairPoint.push_back(stairPoint);
					}
				}
			}

			CHidden* hidden = new CHidden(1142, 180, 20, 35, HIDDEN_TYPE_STOP_CREATE_GHOST);
			listHidden.push_back(hidden);

			//Simon
			simon->stopAutoGoX();
			simon->setWeapon(simon->getWeapon());
			//simon->setSubWeapon(simon->getSubWeapon());
			simon->setDirection(1);
			simon->SetPosition(50.0f, 0); //simon
			objects.push_back(simon);

		/*	CMonneyEffect* money = new CMonneyEffect(200, 60);
			money->SetState(100);
			objects.push_back(money);*/
			CHidden* hiddenTunnel = new CHidden(1592, 222, 14, 5, HIDDEN_TYPE_GO_TUNNEL);
			objects.push_back(hiddenTunnel);

		 
			

			//Whip
			objects.push_back(simon->getWeapon());
			if (simon->getSubWeapon()) {
				simon->setSubWeapon(simon->getSubWeapon());
				objects.push_back(simon->getSubWeapon());
			}

			CHidden* hiddenPanther1 = new CHidden(468, 180, 20, 25, HIDDEN_TYPE_SWITCH_START_STOP_CREATE_PANTHER);
			listHidden.push_back(hiddenPanther1);

			CHidden* hiddenPanther2 = new CHidden(1240, 180, 20, 25, HIDDEN_TYPE_SWITCH_START_STOP_CREATE_PANTHER);
			listHidden.push_back(hiddenPanther2);


			CHidden* hiddenCreateBat = new CHidden(1600, 86, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat);

			CHidden* hiddenCreateBat1 = new CHidden(1673, 121, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat1);
			CHidden* hiddenCreateBat2 = new CHidden(1728, 183, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat2);
			CHidden* hiddenCreateBat3 = new CHidden(1661, 183, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat3);
			CHidden* hiddenCreateBat4 = new CHidden(1536, 183, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat4);
			CHidden* hiddenCreateBat5 = new CHidden(1606, 183, 5, 25, HIDDEN_TYPE_START_CREATE_BAT);
			listHidden.push_back(hiddenCreateBat5);


		/*	CPanther* panther1 = new CPanther(691, 40, -1, simon);
			panther1 = new CPanther(691, 40, -1, simon);
			objects.push_back(panther1);
			listEnemy.push_back(panther1);

			CPanther* panther2 = new CPanther(691, 40, -1, simon);
			panther2 = new CPanther(855, 40, -1, simon);
			objects.push_back(panther2);
			listEnemy.push_back(panther2);

			CPanther* panther3 = new CPanther(691, 40, -1, simon);
			panther3 = new CPanther(921, 40, -1, simon);
			objects.push_back(panther3);
			listEnemy.push_back(panther3);*/

			/*CGhost* newGhost = new CGhost(100, 20, -1);
			objects.push_back(newGhost);
			listEnemy.push_back(newGhost);
			newGhost = new CGhost(350, 20, 1);
			objects.push_back(newGhost);
			listEnemy.push_back(newGhost);*/

			//Map
			maps->Add(ID_MAP_2, map);
			currentIdMap = ID_MAP_2;
		}
	else if (getStage() == 3) {
		cout << "load stage 3" << endl;
		objects.clear();
		listBrick.clear();
		listHidden.clear();
		listStairPoint.clear();
		listDoor.clear();
		/*	for (int i = 0; i < objects.size(); i++) {
					objects.erase(objects.begin() + i);
			}*/

		//listHidden.clear();
		CTextures* textures = CTextures::GetInstance();

		textures->Add(ID_TEX_MAP_3, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));




		CMap* map = new CMap(ID_TEX_MAP_3, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
		map->ReadMapTXT("Map\\Map3.txt");
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
				else if (gameObjectId == 28) {
					for (int i = 0; i < NUMBER_OF_BRICK; i++)
					{
						float l, t, r, b;
						CBrick* brick = new CBrick();
						brick->SetPosition(0 + i * 16.0f, SCREEN_HEIGHT - 30);
						objects.push_back(brick);
						listBrick.push_back(brick);
					}
				}
			};


		}

		//Load new object
		TiXmlDocument Map2Object("XML/Map21_Objects.xml");
		if (!Map2Object.LoadFile())
		{
			DebugOut(L"Can't read XML file: %s");
			MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
			return;
		}
		// get info root
		root = Map2Object.RootElement();
		TiXmlElement* Objects = nullptr;
		TiXmlElement* Object = nullptr;
		for (Objects = root->FirstChildElement(); Objects != NULL; Objects = Objects->NextSiblingElement())
		{
			int id;
			float x, y, Width, Height, direction, center;
			float isThroughBrick;
			Objects->QueryIntAttribute("id", &id);
			for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
			{
				Object->QueryFloatAttribute("x", &x);
				Object->QueryFloatAttribute("y", &y);
				Object->QueryFloatAttribute("width", &Width);
				Object->QueryFloatAttribute("height", &Height);
				Object->QueryFloatAttribute("direction", &direction);
				Object->QueryFloatAttribute("center", &center);
				Object->QueryFloatAttribute("isThroughBrick", &isThroughBrick);

				if (id == 0)
				{
					CBrick* newBrick = new CBrick();
					newBrick->setSize(Width, Height);
					newBrick->SetPosition(x, y);
					listBrick.push_back(newBrick);
					objects.push_back(newBrick);
				}

				if (id == 2) {
					CSmallCandle* smallCandle = new CSmallCandle();
					smallCandle->SetPosition(x, y);
					objects.push_back(smallCandle);
				}
				//else if (id == -1) {
				//	CDoor* door = new CDoor(x, y, 2); //2: id stage 2 , stage cua cua dang dung
				//	door->SetState(DOOR_STATE_STATIC);
				//	objects.push_back(door);
				//	listDoor.push_back(door);
				//}
				else if (id == -3)
				{
					CStairPoint* stairPoint = new CStairPoint(x, y, Width, Height, direction);
					stairPoint->setCenter(center);
					stairPoint->setHasThrough(isThroughBrick);
					objects.push_back(stairPoint);
					listStairPoint.push_back(stairPoint);
				}
			}
		}

		/*CFishMen* fish = new CFishMen(100, 400, 1, simon);
		objects.push_back(fish);
		listEnemy.push_back(fish);

		  fish = new CFishMen(23000, 400, -1, simon);
		objects.push_back(fish);
		listEnemy.push_back(fish);*/
		//Simon
		//simon->setWeapon(simon->getWeapon());
		//simon->setSubWeapon(simon->getSubWeapon());
		simon->setDirection(1);
		//simon->SetPosition(100, 0); //simon
		objects.push_back(simon);


		CHidden* waterHidden = new CHidden(0, 200, 447, 4, HIDDEN_TYPE_SIMON_DIE);
		listHidden.push_back(waterHidden);


		/*	CMonneyEffect* money = new CMonneyEffect(200, 60);
			money->SetState(100);
			objects.push_back(money);*/
		//CHidden* hiddenTunnel = new CHidden(1592, 222, 14, 5, HIDDEN_TYPE_GO_TUNNEL);
		//objects.push_back(hiddenTunnel);

		//Whip
		objects.push_back(simon->getWeapon());
		if (simon->getSubWeapon()) {
			simon->setSubWeapon(simon->getSubWeapon());
			objects.push_back(simon->getSubWeapon());
		}
		
		
			//Map

		/*CFishMen* fish = new  CFishMen(100, 400, 1, simon);
		listEnemy.push_back(fish);
		objects.push_back(fish);*/

		maps->Add(ID_MAP_3, map);
		currentIdMap = ID_MAP_3;
		}
	
	else {
			cout << "CANNOT SET STAGE or STAGE NULL" << endl;
	}
}
void CSceneGame::checkUpdateScene() {
	switch (getStage())
	{
	case 1:
		if (simon->getIsCollisionWithDoor()&&simon->getIsAutoGoXComplete()) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(2);
			cout << "auto x man 1" << endl;
			LoadResources();
		}
		break;
	case 2:
		break;
	case 3:
	default:
		break;
	}
}
void CSceneGame::Update(DWORD dt) {
	
	if (getStage() ==2) {
		
		//createBat();
		/*Check and process Simon on stair*/
	
		/*if (stairPoint) {
			simon->goOnStair(stairPoint);
		}*/
		/*Check and process Simon on stair*/
	}
	else if (getStage() == 3) {
		isAllowCreateFishmen = true;
	
	}
	CStairPoint* stairPoint = simon->checkCollisionStartStair(listStairPoint);
	createFishMan();
	//Create enemy area
	createGhost();
	createBat();
	createPanther();
	checkUpdateScene();

	//bug khong co whip cho simon
	whip->SetPosition(simon->GetPositionX(), simon->GetPositionY());
	vector<LPGAMEOBJECT> coPlayerAndBackground;
	vector<LPGAMEOBJECT> coWeaponAndCandle;
	vector<LPGAMEOBJECT> coEffects;
	vector<LPGAMEOBJECT> coEnemyAndBackground;
	vector<LPGAMEOBJECT> coCommons;
	
	//Update in the new way
	for (int i = 0; i < listEnemy.size(); i++) {
		if (listEnemy[i]->isShow()) {
			listEnemy[i]->Update(dt, &listBrick);
		}
	}
	/*for (int i = 0; i < listStairPoint.size(); i++) {
		listStairPoint[i]->Update(dt, &coPlayerAndBackground);
	}*/



	//simon->Update(dt, &listEnemy);


	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->isShow()) {
			deleteObject(objects, i);
		}
	}
	
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getHealth()>0 && objects[i]->isShow()) {
			
			if (dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				coPlayerAndBackground.push_back(objects[i]);
			}

			else if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])|| dynamic_cast<CSmallCandle*>(objects[i])) {
				coWeaponAndCandle.push_back(objects[i]);
			}
			else if (dynamic_cast<CEffect*>(objects[i])) {
				coEffects.push_back(objects[i]);
			}
			/*else if (dynamic_cast<CBrick*>(objects[i])) {
				coEnemyAndBackground.push_back(objects[i]);
			}*/
			/*else {
				coCommons.push_back(objects[i]);
			}*/
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getHealth() > 0 && objects[i]->isShow()) {

			if (dynamic_cast<CBrick*>(objects[i]) || dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				objects[i]->Update(dt, &coPlayerAndBackground);
			}

			else if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])|| dynamic_cast<CSmallCandle*>(objects[i])) {
				objects[i]->Update(dt, &coWeaponAndCandle);
			}
			else if (dynamic_cast<CEffect*>(objects[i])) {
				objects[i]->Update(dt, &coEffects);
			}
			/*else if (dynamic_cast<CBrick*>(objects[i])) {
				objects[i]->Update(dt, &coEnemyAndBackground);
			}*/
			/*else {
				objects[i]->Update(dt, &coCommons);
			}*/

		}
	}
	//Process cross effect
	if (GetTickCount() - timeStartCrossEffect >= TIME_CORSS_EFFECT) {
		hasCrossEffect = false;
		game->setIsBlinkScene(false);
	}

	if (isStopWatch) {
		if (GetTickCount() - timeStartStopWatch >= TIME_STOP_WATCH) {
			isStopWatch = false;
		}
		for (int i = 0; i < objects.size(); i++) {
			if (!dynamic_cast<CSimon*>(objects[i])) {
				objects[i]->setVx(0);
				objects[i]->setVy(0);
			}
		}
	}

	//Check collision area
	
	checkCollisonOfWeapon(coWeaponAndCandle);
	checkCollisionOfSimon();
	checkCollisionOfEnemy();
	checkCollisionSimonWithHidden();
	simon->collisionWithEnemy(listEnemy);
	// Update camera to follow SIMON
	float cx, cy, camX, camY;
	simon->GetPosition(cx, cy);

	camX = CGame::GetInstance()->GetCamPos_x();
	camY = CGame::GetInstance()->GetCamPos_y();
	//Khoảng cách để Simon vô giữa màn hình

	updateCamAutoGo(dt);
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
		if (camX  >= 1235 && cx >= 1235) {
			CGame::GetInstance()->SetCamPos(camX, CAM_Y_DEFAULT_STAGE_2);
		}
	 
		if (isStageMoving) {
			CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamPos_x() +1 , CAM_Y_DEFAULT_STAGE_2);
			if (round(CGame::GetInstance()->GetCamPos_x()) >= game->getTargetAutoGo()) {
				CGame::GetInstance()->SetCamPos(game->getTargetAutoGo(), CAM_Y_DEFAULT_STAGE_2);
				isStageMoving = false;
			/*	setStage(3);
				LoadResources();*/
			}
		}

		//check chuyen qua cua stage 2
		if (isProcessStageChange && !isStageMoving) {
			for (int i = 0; i < objects.size(); i++) {
				if (dynamic_cast<CDoor*>(objects[i])) {
					if (dynamic_cast<CDoor*>(objects[i])->getId() == 2&!isWaitSimonThroughScene) //dang xu ly cua o stage 2
					{
						isWaitSimonThroughScene = true;
						objects[i]->SetState(DOOR_STATE_OPEN);
						currentDoor = dynamic_cast<CDoor*>(objects[i]);
						simon->autoGoX(1, SIMON_WALKING_SPEED_AUTO, 1600);
					}
				}
			}
		}

		if (!isChangeSceneComplete&&isWaitSimonThroughScene && !simon->getAutoGoX()) {
			simon->setFreeze(true);
			game->setAutoGo(true, 1537);
			isChangeSceneComplete = true;
			currentDoor->SetState(DOOR_STATE_CLOSE);
		}
		//block simon when simon through the door 
	/*	if (isChangeSceneComplete && !game->getAutoGo()) {
			simon->setFreeze(false);
			cout << "set true bat" << endl;
		}*/
		//check chuyen qua cua stage 2
	}
	else if (getStage() == 3) {
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT_STAGE_2); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 
		if (camX >= BOUNDARY_CAMERA_STAGE_3 && cx >= BOUNDARY_CAMERA_STAGE_3) {
			CGame::GetInstance()->SetCamPos(497, CAM_Y_DEFAULT_STAGE_2);
		}
	}

}
void CSceneGame::Render() {
	maps->Get(currentIdMap)->Render();
	for (int i = 0; i < listEnemy.size(); i++)
	{
		listEnemy[i]->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
			objects[i]->Render();
	}
	for (int i = 0; i < listHidden.size(); i++)
	{
		listHidden[i]->Render();
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

void CSceneGame::checkCollisionOfSimon() {
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CItem*>(objects[i])) {
			if (!dynamic_cast<CItem*>(objects[i])->getFinish()) {
				if (simon->isCollisionWithItem(dynamic_cast<CItem*>(objects[i]))) {
					getBonusFromItem(dynamic_cast<CItem*>(objects[i]));
					objects[i]->hide();
					//deleteObject(objects, i);
				}
			}
			
		}
		if (dynamic_cast<CDoor*>(objects[i])) {
			if (simon->checkAABBWithObject(objects[i])) {
				isProcessStageChange = true;
				//simon->SetSpeed(0, simon->getVy());
				simon->setFreeze(true);
				game->setAutoGo(true, 1380);
			}
		}
		if (dynamic_cast<CHidden*>(objects[i])) {
			if (simon->checkAABBWithObject(objects[i])&& (dynamic_cast<CHidden*>(objects[i])->getTypeHidden()== HIDDEN_TYPE_GO_TUNNEL)){
				cout << "chuyen qua stage 3" << endl;
				CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(3);
				LoadResources();
				//set position of simon after go to the tunnel
				simon->SetPosition(33, 25);
				simon->setIsThroughBrick(0);
				cout << "update" << endl;
			}
		}
	}
}
void CSceneGame::checkCollisonOfWeapon(vector<LPGAMEOBJECT> &listObjects) {
	CWeapon* weapon = simon->getWeapon();
	CWeapon* subWeapon = simon->getSubWeapon();
	if (subWeapon) {
		if ((dynamic_cast<CHolyWater*>(subWeapon))&& (dynamic_cast<CHolyWater*>(subWeapon))->getHasFire()) {
			objects.push_back(new CFire(subWeapon->GetPositionX(), subWeapon->GetPositionY(), FIRE_STATE_POND));
		}
		if (subWeapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
			for (int i = 0; i < listObjects.size(); i++) {
				if (dynamic_cast<CCandle*>(listObjects[i]) && subWeapon->checkAABBWithObjectAABBEx(listObjects[i])) {
					subWeapon->setFinish(true);
					objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(dynamic_cast<CCandle*>(listObjects[i])->getId(), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					subWeapon->setCurrentFrame(-1);
					subWeapon->setCanDestroy(false);
					//deleteObject(objects, i);
					subWeapon->setFinish(true);
					listObjects[i]->hide();
					//objects.push_back(new CFire(subWeapon->GetPositionX(), subWeapon->GetPositionY(), FIRE_STATE_POND));
				}
				else if (dynamic_cast<CSmallCandle*>(listObjects[i]) && subWeapon->checkAABBWithObject(listObjects[i])) {
					objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(rand() % (21) + 1, listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					subWeapon->setCurrentFrame(-1);
					subWeapon->setCanDestroy(false);
					//deleteObject(objects, i);
					listObjects[i]->hide();
					subWeapon->setFinish(true);
					//objects.push_back(new CFire(subWeapon->GetPositionX(), subWeapon->GetPositionY(), FIRE_STATE_POND));
				}
			}
		}
	}
	if (weapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
		for (int i = 0; i < listObjects.size(); i++) {
			if (dynamic_cast<CCandle*>(listObjects[i]) && weapon->checkAABBWithObject(listObjects[i])) {
				objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
				objects.push_back(getItem(dynamic_cast<CCandle*>(listObjects[i])->getId(), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					weapon->setCurrentFrame(-1);
					weapon->setCanDestroy(false);
					//deleteObject(objects, i);
					listObjects[i]->hide();
					weapon->setFinish(true);
			}
			else if (dynamic_cast<CSmallCandle*>(listObjects[i]) && weapon->checkAABBWithObject(listObjects[i])) {
				objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
				objects.push_back(getItem(1 + rand() % (11), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
				weapon->setCurrentFrame(-1);
				weapon->setCanDestroy(false);
				//deleteObject(objects, i);
				listObjects[i]->hide();
				weapon->setFinish(true);
			}
			else {
				weapon->setCanDestroy(false);
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
		simon->collectWhipUpgrade(whip);
		whip->setLevel(whip->getLevel() + 1);
	}
	else if (dynamic_cast<CDaggerItem*>(item)) {
		CDagger* dagger = new CDagger();
		cout << "dagger" << endl;
		dagger->SetPosition(simon->GetPositionX(), simon->GetPositionY());
		objects.push_back(dagger);
		simon->setSubWeapon(dagger);
	}
	else if (dynamic_cast<CCross*>(item)) {
		game->setIsBlinkScene(true);
		cout << "ac cross" << endl;
		hasCrossEffect = true;
		timeStartCrossEffect = GetTickCount();
		for (int i = 0; i < listEnemy.size(); i++) {
			listEnemy[i]->hide();
			
			objects.push_back(new CFire(listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
			listEnemy.clear();
		}

	}
	else if (dynamic_cast<CHolyWaterItem*>(item)) {
		CHolyWater* holyWater = new CHolyWater();
		objects.push_back(holyWater);
		cout << "Dang dung vao holywater" << endl;
		simon->setSubWeapon(holyWater);
	}
	else if (dynamic_cast<CMoney*>(item)) {
		cout << "Dang dung vao money" << endl;
		int value = dynamic_cast<CMoney*>(item)->getValue();
		CMonneyEffect* moneyEffect = new CMonneyEffect(item->GetPositionX() + 10, item->GetPositionY() - 30, value);
		objects.push_back(moneyEffect);
	}
	else if (dynamic_cast<CPotRoast*>(item)) {
		//Increase simon score in the board
		cout << "Dang dung vao poproat" << endl;
	}
	else if (dynamic_cast<CSmallHeart*>(item)) {
		//Increase simon score in the board
		cout << "Dang dung vao smallheart" << endl;
	}
	else if (dynamic_cast<CStopWatch*>(item)) {
		isStopWatch = true;
		cout << "Dang dung vao stopwatch" << endl;
		cout << "an stop watch" << endl;
		timeStartStopWatch = GetTickCount();
	}
}
CItem* CSceneGame::getItem(int id, float x, float y) {
	int valueMoney[] = { 100, 400, 700, 1000 };
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
	case 6:
		return new CCross(x, y);
		break;
	case 7:
		return new CHolyWaterItem(x, y);
		break;
	case 8:
		return new CLargeHeart(x, y);
		break;
	case 9:
		return new CLargeHeart(x, y);
		break;
	case 10:
		return new CLargeHeart(x, y);
		break;
	case 11:
		return new CLargeHeart(x, y);
		break;
	case 12:
		return new CLargeHeart(x, y);
		break;
	case 13:
		return new CLargeHeart(x, y);
		break;
	case 14:
		return new CMoney(x, y, valueMoney[rand() % (4)]);
		break;
	case 15:
		return new CPotRoast(x, y);
		break;
	case 16:
		return new CSmallHeart(x, y);
		break;
	case 17:
		return new CStopWatch(x, y);
		break;
	case 18:
		return new CSmallHeart(x, y);
		break;
	case 19:
		return new CSmallHeart(x, y);
		break;
	case 20:
		return new CSmallHeart(x, y);
		break;
	case 21:
		return new CSmallHeart(x, y);
		break;
	default:
		return new CLargeHeart(x, y);
		break;
	}
}
void CSceneGame::deleteObject(vector<LPGAMEOBJECT> &listObj, int index) {
	listObj.erase(listObj.begin() + index);
}

void CSceneGame::checkCollisionOfEnemy() {
	CWeapon* weapon = simon->getWeapon();
	CWeapon* subWeapon = simon->getSubWeapon();
	if (subWeapon) {
		if (subWeapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
			for (int i = 0; i < listEnemy.size(); i++) {
				if (listEnemy[i]->isShow() && listEnemy[i]->getType() == TYPE_OBJECT_ENEMY && subWeapon->checkAABBWithObjectAABBEx(listEnemy[i])) {
					objects.push_back(new CFire(listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
					objects.push_back(getItem(1 + rand() % (11), listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
					subWeapon->setCurrentFrame(-1);
					subWeapon->setCanDestroy(false);
					subWeapon->setCurrentFrame(-1);
					cout << "Va cham enemy" << endl;
					//deleteObject(objects, i);
					listEnemy[i]->hide();
					//subWeapon->setFinish(true);
				}
			}
		}
	}
	if (weapon->getCurrentFrame()==3) { //Vu khi dang hoat dong moi xet va cham
		for (int i = 0; i < listEnemy.size(); i++) {
			if (listEnemy[i]->isShow()&&listEnemy[i]->getType()== TYPE_OBJECT_ENEMY && weapon->checkAABBWithObjectAABBEx(listEnemy[i])) {
				objects.push_back(new CFire(listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
				objects.push_back(getItem(1 + rand() % (11), listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
				weapon->setCurrentFrame(-1);
				weapon->setCanDestroy(false);
				weapon->setCurrentFrame(-1); 
				cout<<"Va cham enemy"<<endl;
				//deleteObject(objects, i);
				listEnemy[i]->hide();
				weapon->setFinish(true);
			}
		}

	}
	else {
		//cout << "Undame" << endl;
	}
}
void CSceneGame::createBat() {

	if (isAllowCreateBat) {
	
		int nBat = 0;
		for (int i = 0; i < objects.size(); i++) {
			if (dynamic_cast<CBat*>(objects[i]) && objects[i]->isShow()) {
				nBat++;
			}
		}

		if (nBat == 0) {
			int randomInt = game->getRandomInt(1, 3);
			if (randomInt % 2 == 0) {
				CBat* bat = new CBat(game->GetCamPos_x(), simon->GetPositionY() /*+ game->getRandomInt(-4, 20)*/, 1);
				listEnemy.push_back(bat);
				objects.push_back(bat);
			}
			else {
				CBat* bat = new CBat(game->GetCamPos_x() + SCREEN_WIDTH, simon->GetPositionY()/* + game->getRandomInt(-4, 20)*/, -1);
				listEnemy.push_back(bat);
				objects.push_back(bat);
			}
			isAllowCreateBat = false;
		}
	}
}
void CSceneGame::createGhost() {
	
	if (!isAllowToCreateGhost) {
		return;
	 }
	
	int ghost = 0;
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CGhost*>(objects[i])&&objects[i]->isShow()) {
			ghost++;
		}
	}

	if (ghost == 0&&!isWaitingToCreateGhost) {
		timeStartCreateGhost = GetTickCount();
		isWaitingToCreateGhost = true;
	}
	if (GetTickCount() - timeStartCreateGhost >= TIME_DELAY_CREATE_GHOST&& isWaitingToCreateGhost) {
			for (int i = 0; i < 3; i++) {
				if (rand() % 2) {
					CGhost* newGhost = new CGhost(game->GetCamPos_x() - i * 30, 170, 1); // Direction: 1 la di qua phai, -1 la di qua trai
					listEnemy.push_back(newGhost);
					objects.push_back(newGhost);
					cout << "Tao ghost phai" << endl;
				}
				else {
					CGhost* newGhost = new CGhost(game->GetCamPos_x() + SCREEN_WIDTH + i * 30, 170, -1); // Direction: 1 la di qua phai, -1 la di qua trai
					listEnemy.push_back(newGhost);
					objects.push_back(newGhost);
					cout << "Tao ghost phai" << endl;
				}

			}
			
			isWaitingToCreateGhost = false;
	}
}

void CSceneGame::updateCamAutoGo(DWORD dt) {
	float camX = CGame::GetInstance()->GetCamPos_x();
	if (game->getAutoGo() && camX!=game->getTargetAutoGo()) {
		//CGame::GetInstance()->SetCamPos(camX+100, CAM_Y_DEFAULT_STAGE_1);
		isStageMoving = true;
	}
}
void CSceneGame::createFishMan() {
	if (!isAllowCreateFishmen) {
		return;
	}

	int nFishMen = 0;
	for (int i = 0; i < listEnemy.size(); i++) {
		if (dynamic_cast<CFishMen*>(listEnemy[i])&& listEnemy[i]->isShow()) {
			nFishMen++;
		}
	}
	cout << "fishmen: " << nFishMen << endl;
	if (nFishMen < 2)
	{
		DWORD now = GetTickCount();
		if (GetTickCount()- TimeCreateFishmen >=TimeWaitCreateFishmen) // đủ thời gian chờ
		{
			cout << "Dang thuc hien tao fish" << endl;
			TimeCreateFishmen = now; // đặt lại thời gian đã tạo

			float xFishmen = 0;

			if (FISHMEN_ZONE_1_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_1_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4);
			}

			if (FISHMEN_ZONE_2_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_2_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_1) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));
			}

			if (FISHMEN_ZONE_3_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_3_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_5);
			}

			if (FISHMEN_ZONE_4_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_4_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_5);
			}

			if (FISHMEN_ZONE_5_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_5_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_6);
			}

			if (FISHMEN_ZONE_6_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_6_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_5) : ((rand() % 2) ? (FISHMEN_POS_7) : (FISHMEN_POS_8));
			}

			if (FISHMEN_ZONE_7_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_7_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_8);
			}
			if (FISHMEN_ZONE_8_LEFT < simon->GetPositionX() && simon->GetPositionX() <= FISHMEN_ZONE_8_RIGHT)
			{
				xFishmen = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_7);
			}
			int directionFishmen = xFishmen < simon->GetPositionX() ? 1 : -1;


			float yFishmen = FISHMEN_POS_Y;

		

			CFishMen* newFishMan = new CFishMen(xFishmen, yFishmen, directionFishmen, simon, &listEnemy);
			listEnemy.push_back(newFishMan);
			objects.push_back(newFishMan);
			cout << "Tao fishmen" << endl;
			createSplash(xFishmen, yFishmen);
			
			TimeWaitCreateFishmen = 2000 + (rand() % 2000);
		}
	}
}

void CSceneGame::checkCollisionSimonWithHidden() {
	int typeHidden = simon->getTypeHiddenCollision(listHidden);
	switch (typeHidden)
	{
	case HIDDEN_TYPE_STOP_CREATE_GHOST:
		isAllowToCreateGhost = false;
		break;
	case HIDDEN_TYPE_SWITCH_START_STOP_CREATE_PANTHER:
		isAllowToCreatePanther = true;
		/*if (!isUpdateCreatePantherStatus) {
			isAllowToCreatePanther = !isAllowToCreatePanther;
			cout << "va cham panther hidden" << endl;
			isUpdateCreatePantherStatus = true;
	}*/
		break;
	case HIDDEN_TYPE_SIMON_DIE:
		if (simon->isShow()) {
			simon->hide();
			createSplash(simon->GetPositionX(), simon->GetPositionY());
		}
		break;
	case HIDDEN_TYPE_START_CREATE_BAT:
		isAllowCreateBat = true;
		cout << "Aloow creawte bat" << endl;
		break;
	default:
		isUpdateCreatePantherStatus = false;
		break;
	}
}

void CSceneGame::createPanther()
{
	if (!isAllowToCreatePanther) {
		return;
	}
	int panther = 0;
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CPanther*>(objects[i]) && objects[i]->isShow()) {
			panther++;
		}
	}
	if (panther == 0) {
		cout << "Create panther" << endl;
		CPanther* panther1 = new CPanther(691, 40, -1, simon);
		panther1 = new CPanther(691, 40, -1, simon);
		objects.push_back(panther1);
		listEnemy.push_back(panther1);

		CPanther* panther2 = new CPanther(691, 40, -1, simon);
		panther2 = new CPanther(855, 40, -1, simon);
		objects.push_back(panther2);
		listEnemy.push_back(panther2);

		CPanther* panther3 = new CPanther(691, 40, -1, simon);
		panther3 = new CPanther(921, 40, -1, simon);
		objects.push_back(panther3);
		listEnemy.push_back(panther3);

		isAllowToCreatePanther = false;
	}
}

void CSceneGame::createSplash(float x,float y) {
	for (int i = 0; i < QUANTITY_EFFECT_SPLASH; i++)
	{
		if (i == 0)
		{
			y = SPLASH_Y_SIDE;
		}
		else if (i == 1)
		{
			y = SPLASH_Y_CENTER;
			x = x + SPLASH_OFFSET_LEFT;
		}
		else
		{
			y = SPLASH_Y_SIDE;
			x = x + SPLASH_OFFSET_RIGHT;
		}
		CEffect* splash = new CSplash(x, y);
		objects.push_back(splash);
	}
}
