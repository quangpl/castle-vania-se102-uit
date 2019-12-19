#include "SceneGame.h"

CGame* game = CGame::GetInstance();
CSimon* simon = CSimon::GetInstance();
CMaps* maps = CMaps::GetInstance();
CWhip* whip;
CWeapon* backupWeapon;
CWeapon* backupSubWeapon;
CSceneGame* CSceneGame::__instance = NULL;
vector<CItem*> listItem;
vector<CEffect*> listEffect;

vector<CGameObject*> listHidden;
vector<CGameObject*> listBrick;
vector<CGameObject*> listSoftBrick;


vector<CGameObject*> listCandle;

vector<CGameObject*> listStairPoint;
vector<CDoor*> listDoor;


vector<CGameObject*> listEnemy;
CDoor* currentDoor;
CGrid* grid = new CGrid();


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
	grid->clear();
	if (getStage() == 1) {
		objects.clear();
		grid->clear();
		CTextures* textures = CTextures::GetInstance();
/*
		textures->Add(ID_TEX_MAP_1, "Map\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
		textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));
		textures->Add(ID_TEX_ENEMY, "textures\\enemy.png", D3DCOLOR_XRGB(96, 68, 106));*/




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
			//DebugOut(L"Can't read XML file");
			MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
			return;
		}
		else
		{
			//DebugOut(L"[INFO]Read XML success\n");
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
			};
		}
		
		//Load new object
		TiXmlDocument Map2Object("XML/Map1_Objects.xml");
		if (!Map2Object.LoadFile())
		{
			//DebugOut(L"Can't read XML file: %s");
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
			float typeHidden, idCandle;
			Objects->QueryIntAttribute("id", &id);
			for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
			{
				Object->QueryFloatAttribute("x", &x);
				Object->QueryFloatAttribute("y", &y);
				Object->QueryFloatAttribute("width", &Width);
				Object->QueryFloatAttribute("height", &Height);
				Object->QueryFloatAttribute("typeHidden", &typeHidden);
				Object->QueryFloatAttribute("idCandle", &idCandle);

				if (id == 9) {
					CHidden* hidden = new CHidden(x, y, Width, Height, typeHidden);
					listHidden.push_back(hidden);
				}
				else if (id == 0)
				{
					CBrick* newBrick = new CBrick();
					newBrick->setSize(Width, Height);
					newBrick->SetPosition(x, y);
					listBrick.push_back(newBrick);
					objects.push_back(newBrick);
				}
				else if (id == 1) {
					CCandle* candle = new CCandle();
					candle->SetState(CANDLE_STATE_SHOW);
					candle->SetPosition(x, y);
					candle->setId(idCandle);
					//listCandle.push_back(candle);
					objects.push_back(candle);
				}
			}
		}
		

		simon->SetPosition(50.0f, 0); //simon
		simon->setWeapon(whip);
		objects.push_back(simon);


		objects.push_back(whip);
		maps->Add(ID_MAP_1, map);
		currentIdMap = ID_MAP_1;


	}
	else if (getStage() == 2) 
		{
		//cout << "load stage 2" << endl;
			objects.clear();
			listHidden.clear();
			listStairPoint.clear();
			listDoor.clear();
			listEnemy.clear();
			listCandle.clear();
			listBrick.clear();
			grid->clear();

			//config init constant
			isAllowToCreateGhost = true;
			
			listHidden.clear();
			CTextures* textures = CTextures::GetInstance();

			/*textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
			textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
			textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
			textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));*/




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
				//DebugOut(L"Can't read XML file");
				MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
				return;
			}
			else
			{
				//DebugOut(L"[INFO]Read XML success\n");
			}
			// get info root
			TiXmlElement* root = doc.RootElement();
			TiXmlElement* sprite = nullptr;
			TiXmlElement* animation = nullptr;
			TiXmlElement* texture = nullptr;
			LPANIMATION ani;
			int nItem = 1;

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
				//DebugOut(L"Can't read XML file: %s");
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
				float isThroughBrick, typeHidden;
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
					Object->QueryFloatAttribute("typeHidden", &typeHidden);

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
						//listCandle.push_back(smallCandle);
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
						listStairPoint.push_back(stairPoint);
					}
					else if (id == 9)
					 {
						 CHidden* hidden = new CHidden(x, y, Width, Height, typeHidden);
						 listHidden.push_back(hidden);
					 }
				}
			}


			//Simon
			simon->stopAutoGoX();
			simon->setWeapon(simon->getWeapon());
			simon->setDirection(1);
			simon->SetPosition(50.0f, 0); //simon
			objects.push_back(simon);



		 
			

			//Whip
			objects.push_back(simon->getWeapon());
			if (simon->getSubWeapon()) {
				simon->setSubWeapon(simon->getSubWeapon());
				objects.push_back(simon->getSubWeapon());
			}



			//Map
			maps->Add(ID_MAP_2, map);
			currentIdMap = ID_MAP_2;
		}
	else if (getStage() == 3) {
		//cout << "load stage 3" << endl;
		objects.clear();
		listBrick.clear();
		listHidden.clear();
		listStairPoint.clear();
		listDoor.clear();
		listEnemy.clear();
		grid->clear();
		listSoftBrick.clear();
		listCandle.clear();

		//isAllowCreateFishmen = false;
		isAllowCreateFishmen = true;
		CTextures* textures = CTextures::GetInstance();

		/*textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
		textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
		textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));*/




		CMap* map = new CMap(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
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
			//DebugOut(L"Can't read XML file");
			MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
			return;
		}
		else
		{
			//DebugOut(L"[INFO]Read XML success\n");
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
		TiXmlDocument Map2Object("XML/Map21_Objects.xml");
		if (!Map2Object.LoadFile())
		{
			//DebugOut(L"Can't read XML file: %s");
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
			float isThroughBrick, typeHidden;
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
				Object->QueryFloatAttribute("typeHidden", &typeHidden);


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
					//listCandle.push_back(smallCandle);
					objects.push_back(smallCandle);
				}
				
				else if (id == -3)
				{
					CStairPoint* stairPoint = new CStairPoint(x, y, Width, Height, direction);
					stairPoint->setCenter(center);
					stairPoint->setHasThrough(isThroughBrick);
					//objects.push_back(stairPoint);
					listStairPoint.push_back(stairPoint);
				}
				else if (id == 9)
				{
					CHidden* hidden = new CHidden(x, y, Width, Height, typeHidden);
					listHidden.push_back(hidden);
				}
			}
		}

		
		//Simon
		simon->setDirection(1);
		objects.push_back(simon);


		//Whip
		objects.push_back(simon->getWeapon());
		if (simon->getSubWeapon()) {
			simon->setSubWeapon(simon->getSubWeapon());
			objects.push_back(simon->getSubWeapon());
		}
		

		maps->Add(ID_MAP_3, map);
		currentIdMap = ID_MAP_3;
		}
	else if (getStage() == 4) {
	//cout << "load stage 4" << endl;
	objects.clear();
	listBrick.clear();
	listHidden.clear();
	listCandle.clear();
	listStairPoint.clear();
	listDoor.clear();
	grid->clear();
	listEnemy.clear();
	listSoftBrick.clear();
	isAllowCreateFishmen = false;

	CTextures* textures = CTextures::GetInstance();

	/*textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));*/




	CMap* map = new CMap(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
	map->ReadMapTXT("Map\\Map4.txt");
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
		//DebugOut(L"Can't read XML file");
		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
		return;
	}
	else
	{
		//DebugOut(L"[INFO]Read XML success\n");
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
	TiXmlDocument Map2Object("XML/Map4_Objects.xml");
	if (!Map2Object.LoadFile())
	{
		//DebugOut(L"Can't read XML file: %s");
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
		float isThroughBrick, typeHidden;
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
			Object->QueryFloatAttribute("typeHidden", &typeHidden);


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
				//listCandle.push_back(smallCandle);
			}
			else if (id == -3)
			{
				CStairPoint* stairPoint = new CStairPoint(x, y, Width, Height, direction);
				stairPoint->setCenter(center);
				stairPoint->setHasThrough(isThroughBrick);
				//objects.push_back(stairPoint);
				listStairPoint.push_back(stairPoint);
			}
			else if (id == 9)
			{
				CHidden* hidden = new CHidden(x, y, Width, Height, typeHidden);
				listHidden.push_back(hidden);
			}
			else if (id == 20)
			{

				CSoftBrick* softBrick = new CSoftBrick(x, y);
				listSoftBrick.push_back(softBrick);

			}
		}
	}


	//Simon
	simon->setDirection(1);
	objects.push_back(simon);

	//Whip
	objects.push_back(simon->getWeapon());
	if (simon->getSubWeapon()) {
		simon->setSubWeapon(simon->getSubWeapon());
		objects.push_back(simon->getSubWeapon());
	}


	//Map


	maps->Add(ID_MAP_4, map);
	currentIdMap = ID_MAP_4;
	}
	
	else {
			//cout << "CANNOT SET STAGE or STAGE NULL" << endl;
	}
	loadObjectToGrid();
}
void CSceneGame::checkUpdateScene() {
	switch (getStage())
	{
	case 1:
		if (simon->getIsCollisionWithDoor()&&simon->getIsAutoGoXComplete()) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(2);
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
	/*Get objects from grid*/
	//cout << objects.size() << endl;
	
	vector<CGameObject*> listObjectFromGrid;
	grid->getAllObjects(listObjectFromGrid);
	listStairPoint.clear();
	listHidden.clear();
	listSoftBrick.clear();

	for (int i = 0; i < listObjectFromGrid.size(); i++) {
		if (listObjectFromGrid[i]->isShow()) {
			if (dynamic_cast<CStairPoint*>(listObjectFromGrid[i])) {
				listStairPoint.push_back(listObjectFromGrid[i]);
			}
			else if (dynamic_cast<CHidden*>(listObjectFromGrid[i])) {
				listHidden.push_back(listObjectFromGrid[i]);
			}
			else if (dynamic_cast<CSmallCandle*>(listObjectFromGrid[i])|| dynamic_cast<CCandle*>(listObjectFromGrid[i])) {
				objects.push_back(listObjectFromGrid[i]);
			}
			else if (dynamic_cast<CSoftBrick*>(listObjectFromGrid[i])) {
				listSoftBrick.push_back(listObjectFromGrid[i]);
			}
		}
	}

	/*Get objects from grid*/

	/*
	if (getStage() ==2) {
		
		
	}
	else if (getStage() == 3) {
		isAllowCreateFishmen = true;
	}*/

	CStairPoint* stairPoint = simon->checkCollisionStartStair(listStairPoint);

	//Create enemy area
	createFishMan();
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

	for (int i = 0; i < listDoor.size(); i++) {
		if (listDoor[i]->isShow()) {
			listDoor[i]->Update(dt);
		}
	}

	/*
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->isShow()) {
			deleteObject(objects, i);
		}
	}*/
	
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
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getHealth() > 0 && objects[i]->isShow()) {

			if (dynamic_cast<CBrick*>(objects[i])|| dynamic_cast<CSimon*>(objects[i]) || dynamic_cast<CItem*>(objects[i])) {
				objects[i]->Update(dt, &coPlayerAndBackground);
			}

			else if (dynamic_cast<CWeapon*>(objects[i]) || dynamic_cast<CCandle*>(objects[i])|| dynamic_cast<CSmallCandle*>(objects[i])) {
				objects[i]->Update(dt, &coWeaponAndCandle);
			}
			else if (dynamic_cast<CEffect*>(objects[i])) {
				objects[i]->Update(dt, &coEffects);
			}
		}
	}


#pragma region Process Cross Effect
	if (GetTickCount() - timeStartCrossEffect >= TIME_CORSS_EFFECT) {
		hasCrossEffect = false;
		game->setIsBlinkScene(false);
	}
#pragma endregion


#pragma region Process Stopwatch Effect
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

#pragma endregion
	if (simon->getFreeze()) {
		cout << "Freeze true" << endl;
	}
	else {
	}

	//Append all objects which weapon can destroy 
	coWeaponAndCandle.reserve(coWeaponAndCandle.size() + listEnemy.size() + listSoftBrick.size()); // Reserve space first
	coWeaponAndCandle.insert(coWeaponAndCandle.end(), listEnemy.begin(), listEnemy.end());
	coWeaponAndCandle.insert(coWeaponAndCandle.end(), listSoftBrick.begin(), listSoftBrick.end());

	checkCollisonOfWeapon(coWeaponAndCandle);

	checkCollisionOfSimon();
	checkCollisionSimonWithHidden();
	simon->collisionWithEnemy(listEnemy);


#pragma region Camera Control
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
			simon->setFreeze(true);
			CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamPos_x() +1.75 , CAM_Y_DEFAULT_STAGE_2);
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
						simon->setFreeze(true);
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
	}
	else if (getStage() == 3) {
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT_STAGE_2); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 
		if (camX >= BOUNDARY_CAMERA_STAGE_3 && cx >= BOUNDARY_CAMERA_STAGE_3) {
			CGame::GetInstance()->SetCamPos(497, CAM_Y_DEFAULT_STAGE_2);
		}
	}
	else if (getStage() == 4) {
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_DEFAULT_STAGE_2); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 
		if (camX >= BOUNDARY_CAMERA_STAGE_3 && cx >= BOUNDARY_CAMERA_STAGE_3) {
			CGame::GetInstance()->SetCamPos(BOUNDARY_CAMERA_STAGE_3, CAM_Y_DEFAULT_STAGE_2);
		}
	}
#pragma endregion

}
void CSceneGame::Render() {
	maps->Get(currentIdMap)->Render();
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy[i]->isShow()) {
			listEnemy[i]->Render();
	}
	}
	for (int i = 0; i < listSoftBrick.size(); i++)
	{
		listSoftBrick[i]->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isShow()) {
			objects[i]->Render();
		}
	}
	for (int i = 0; i < listHidden.size(); i++)
	{
		listHidden[i]->Render();
	}
	for (int i = 0; i < listStairPoint.size(); i++)
	{
		listStairPoint[i]->Render();
	}
	

}
void CSceneGame::loadObjectToGrid() {
	for (int i = 0; i < listStairPoint.size(); i++) {
		grid->addToGrid(listStairPoint[i]);
	}
	for (int i = 0; i < listHidden.size(); i++) {
		grid->addToGrid(listHidden[i]);
	}
	for (int i = 0; i < listCandle.size(); i++) {
		grid->addToGrid(listCandle[i]);
	}
	for (int i = 0; i < listBrick.size(); i++) {
		grid->addToGrid(listBrick[i]);
	}
	for (int i = 0; i < listSoftBrick.size(); i++) {
		grid->addToGrid(listSoftBrick[i]);
	}
}

void CSceneGame::checkCollisionOfSimon() {
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CItem*>(objects[i])) {
			if (!dynamic_cast<CItem*>(objects[i])->getFinish()) {
				if (simon->isCollisionWithItem(dynamic_cast<CItem*>(objects[i]))) {
					getBonusFromItem(dynamic_cast<CItem*>(objects[i]));
					objects[i]->hide();
					cout << "Cham item" << endl;
				}
			}
			
		}
		if (dynamic_cast<CDoor*>(objects[i])) {
			if (simon->checkAABBWithObject(objects[i])) {
				isProcessStageChange = true;
				simon->setFreeze(true);
				game->setAutoGo(true, 1380);
			}
		}
		
	}
}
void CSceneGame::checkCollisonOfWeapon(vector<LPGAMEOBJECT> &listObjects) { //Truyền vào đây những listObject mà weapon đánh được
	CWeapon* weapon = simon->getWeapon();
	CWeapon* subWeapon = simon->getSubWeapon();
	if (subWeapon) {
		if ((dynamic_cast<CHolyWater*>(subWeapon))&& (dynamic_cast<CHolyWater*>(subWeapon))->getHasFire()) {
			objects.push_back(new CFire(subWeapon->GetPositionX(), subWeapon->GetPositionY(), FIRE_STATE_POND));
		}
		if (subWeapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
			for (int i = 0; i < listObjects.size(); i++) {
				if (listObjects[i]->isShow()) {
					if (dynamic_cast<CCandle*>(listObjects[i]) && subWeapon->checkAABBWithObjectAABBEx(listObjects[i])) {
						subWeapon->setFinish(true);
						objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						objects.push_back(getItem(dynamic_cast<CCandle*>(listObjects[i])->getId(), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						subWeapon->setCurrentFrame(-1);
						subWeapon->setCanDestroy(false);
						subWeapon->setFinish(true);
						listObjects[i]->hide();
					}
					else if (dynamic_cast<CSmallCandle*>(listObjects[i]) && subWeapon->checkAABBWithObject(listObjects[i])) {
						objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						objects.push_back(getItem(rand() % (21) + 1, listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						subWeapon->setCurrentFrame(-1);
						subWeapon->setCanDestroy(false);
						listObjects[i]->hide();
						subWeapon->setFinish(true);
					}
					else if (listObjects[i]->getType() == TYPE_OBJECT_ENEMY&& subWeapon->checkAABBWithObjectAABBEx(listObjects[i])) {
						objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						objects.push_back(getItem(1 + rand() % (11), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
						subWeapon->setCurrentFrame(-1);
						subWeapon->setCanDestroy(false);
						listObjects[i]->hide();
						subWeapon->setFinish(true);
					}
				}
			}
		}
	}
	if (weapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
		for (int i = 0; i < listObjects.size(); i++) {
			if (listObjects[i]->isShow()) {
				if (dynamic_cast<CCandle*>(listObjects[i]) && weapon->checkAABBWithObject(listObjects[i])) {
					objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(dynamic_cast<CCandle*>(listObjects[i])->getId(), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					weapon->setCurrentFrame(-1);
					weapon->setCanDestroy(false);
					listObjects[i]->hide();
					weapon->setFinish(true);
				}
				else if (dynamic_cast<CSmallCandle*>(listObjects[i]) && weapon->checkAABBWithObject(listObjects[i])) {
					objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(1 + rand() % (11), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					weapon->setCurrentFrame(-1);
					weapon->setCanDestroy(false);
					listObjects[i]->hide();
					weapon->setFinish(true);
				}
				else if (listObjects[i]->getType() == TYPE_OBJECT_ENEMY&& weapon->checkAABBWithObjectAABBEx(listObjects[i])) {
					objects.push_back(new CFire(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(1 + rand() % (11), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					weapon->setCurrentFrame(-1);
					weapon->setCanDestroy(false);
					weapon->setCurrentFrame(-1);
					listObjects[i]->hide();
					weapon->setFinish(true);
				}
				else if (dynamic_cast<CSoftBrick*>(listObjects[i]) && weapon->checkAABBWithObjectAABBEx(listObjects[i])) {
					objects.push_back(new CSoftBrickEffect(listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					objects.push_back(getItem(1 + rand() % (11), listObjects[i]->GetPositionX(), listObjects[i]->GetPositionY()));
					weapon->setCurrentFrame(-1);
					weapon->setCanDestroy(false);
					weapon->setCurrentFrame(-1);
					listObjects[i]->hide();
					weapon->setFinish(true);
				}
				else {
					weapon->setCanDestroy(false);
						weapon->setCurrentFrame(-1);
				}
			}
		}
	}
}
void CSceneGame::getBonusFromItem(CItem* item) {
	if (dynamic_cast<CLargeHeart*>(item)) {
		//cout << "Dang dung vao heart" << endl;
	}
	else if(dynamic_cast<CWhipUpgrade*>(item)) {
		simon->collectWhipUpgrade(whip);
		whip->setLevel(whip->getLevel() + 1);
	}
	else if (dynamic_cast<CDaggerItem*>(item)) {
		CDagger* dagger = new CDagger();
		dagger->SetPosition(simon->GetPositionX(), simon->GetPositionY());
		objects.push_back(dagger);
		simon->setSubWeapon(dagger);
	}
	else if (dynamic_cast<CCross*>(item)) {
		game->setIsBlinkScene(true);
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
		simon->setSubWeapon(holyWater);
	}
	else if (dynamic_cast<CMoney*>(item)) {
		int value = dynamic_cast<CMoney*>(item)->getValue();
		CMonneyEffect* moneyEffect = new CMonneyEffect(item->GetPositionX() + 10, item->GetPositionY() - 30, value);
		objects.push_back(moneyEffect);
	}
	else if (dynamic_cast<CPotRoast*>(item)) {
	}
	else if (dynamic_cast<CSmallHeart*>(item)) {
	}
	else if (dynamic_cast<CStopWatch*>(item)) {
		isStopWatch = true;
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
		return new CMoney(x, y, valueMoney[rand() % (4)]);
		break;
	case 7:
		return new CMoney(x, y, valueMoney[rand() % (4)]);
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
		return new CSmallHeart(x, y);
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

//void CSceneGame::checkCollisionOfEnemy() {
//	CWeapon* weapon = simon->getWeapon();
//	CWeapon* subWeapon = simon->getSubWeapon();
//	if (subWeapon) {
//		if (subWeapon->getCanDestroy()) { //Vu khi dang hoat dong moi xet va cham
//			for (int i = 0; i < listEnemy.size(); i++) {
//				if (listEnemy[i]->isShow() && listEnemy[i]->getType() == TYPE_OBJECT_ENEMY && subWeapon->checkAABBWithObjectAABBEx(listEnemy[i])) {
//					objects.push_back(new CFire(listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
//					objects.push_back(getItem(1 + rand() % (11), listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
//					subWeapon->setCurrentFrame(-1);
//					subWeapon->setCanDestroy(false);
//					subWeapon->setCurrentFrame(-1);
//					subWeapon->setFinish(true);
//					listEnemy[i]->hide();
//				}
//			}
//		}
//	}
//	if (weapon->getCanDestroy()) {
//		if (weapon->getCurrentFrame() == 3) { //Vu khi dang hoat dong moi xet va cham
//			for (int i = 0; i < listEnemy.size(); i++) {
//				if (listEnemy[i]->isShow() && listEnemy[i]->getType() == TYPE_OBJECT_ENEMY && weapon->checkAABBWithObjectAABBEx(listEnemy[i])) {
//					objects.push_back(new CFire(listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
//					objects.push_back(getItem(1 + rand() % (11), listEnemy[i]->GetPositionX(), listEnemy[i]->GetPositionY()));
//					weapon->setCurrentFrame(-1);
//					weapon->setCanDestroy(false);
//					weapon->setCurrentFrame(-1);
//					listEnemy[i]->hide();
//					weapon->setFinish(true);
//				}
//				else {
//					weapon->setCanDestroy(false);
//				}
//			}
//
//		}
//}
//	else {
//		//cout << "Undame" << endl;
//	}
//}
void CSceneGame::createBat() {

	//if (isAllowCreateBat) {
	//
	//	int nBat = 0;
	//	for (int i = 0; i < objects.size(); i++) {
	//		if (dynamic_cast<CBat*>(objects[i]) && objects[i]->isShow()) {
	//			nBat++;
	//		}
	//	}

	//	if (nBat == 0) {
	//		int randomInt = game->getRandomInt(1, 3);
	//		if (randomInt % 2 == 0) {
	//			CBat* bat = new CBat(game->GetCamPos_x(), simon->GetPositionY() /*+ game->getRandomInt(-4, 20)*/, 1);
	//			listEnemy.push_back(bat);
	//			objects.push_back(bat);
	//		}
	//		else {
	//			CBat* bat = new CBat(game->GetCamPos_x() + SCREEN_WIDTH, simon->GetPositionY()/* + game->getRandomInt(-4, 20)*/, -1);
	//			listEnemy.push_back(bat);
	//			objects.push_back(bat);
	//		}
	//		isAllowCreateBat = false;
	//	}
	//}
}
void CSceneGame::createGhost() {
	
	if (!isAllowToCreateGhost) {
		return;
	 }
	
	int ghost = 0;
	for (int i = 0; i < listEnemy.size(); i++) {
		if (dynamic_cast<CGhost*>(listEnemy[i])&& listEnemy[i]->isShow()) {
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
					//objects.push_back(newGhost);
					//cout << "Tao ghost phai" << endl;
				}
				else {
					CGhost* newGhost = new CGhost(game->GetCamPos_x() + SCREEN_WIDTH + i * 30, 170, -1); // Direction: 1 la di qua phai, -1 la di qua trai
					listEnemy.push_back(newGhost);
					//objects.push_back(newGhost);
					//cout << "Tao ghost phai" << endl;
				}

			}
			
			isWaitingToCreateGhost = false;
	}
}

void CSceneGame::updateCamAutoGo(DWORD dt) {
	float camX = CGame::GetInstance()->GetCamPos_x();
	if (game->getAutoGo() && camX!=game->getTargetAutoGo()) {
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
	if (nFishMen < 2)
	{
		DWORD now = GetTickCount();
		if (GetTickCount()- TimeCreateFishmen >=TimeWaitCreateFishmen) // đủ thời gian chờ
		{
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
			//objects.push_back(newFishMan);
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
		break;
	case HIDDEN_TYPE_CHANGE_STAGE_FROM_3_TO_2_TYPE_1:
		if (simon->getDirection() < 0) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(4);
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
			simon->setDirection(-1);
			game->SetCamPos(0, game->GetCamPos_y());
			simon->SetPosition(33.5, 194);
		}
		break;
	case HIDDEN_TYPE_CHANGE_STAGE_FROM_3_TO_2_TYPE_2:
		if (simon->getDirection() < 0) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(4);
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
			simon->setDirection(-1);
			simon->SetPosition(344, 188);
		}
		break;
	case HIDDEN_TYPE_LOAD_STAGE_4:
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(4);
		CScenes::GetInstance()->Get(SCENE_GAME_ID)->LoadResources();
		simon->SetPosition(77, 86);
		simon->stopAutoGoX();
		break;
	case HIDDEN_TYPE_GO_TUNNEL:
		if (!simon->getIsAtTunnel()) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(3);
			LoadResources();
			simon->SetPosition(33, 25);
			simon->setIsThroughBrick(0);
			simon->setIsAtTunnel(true);
		}
		break;
	case HIDDEN_TYPE_GO_TUNNEL_2:
		if (!simon->getIsAtTunnel()&&simon->getDirection()>0) {
			CScenes::GetInstance()->Get(SCENE_GAME_ID)->setStage(3);
			LoadResources();
			simon->SetPosition(352, 32);
			simon->setIsThroughBrick(0);
			simon->setIsAtTunnel(true);
		}
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
	for (int i = 0; i < listEnemy.size(); i++) {
		if (dynamic_cast<CPanther*>(listEnemy[i]) && listEnemy[i]->isShow()) {
			panther++;
		}
	}
	if (panther == 0) {
		//cout << "Create panther" << endl;
		CPanther* panther1 = new CPanther(691, 40, -1, simon);
		panther1 = new CPanther(691, 40, -1, simon);
		//objects.push_back(panther1);
		listEnemy.push_back(panther1);

		CPanther* panther2 = new CPanther(691, 40, -1, simon);
		panther2 = new CPanther(855, 40, -1, simon);
		//objects.push_back(panther2);
		listEnemy.push_back(panther2);

		CPanther* panther3 = new CPanther(691, 40, -1, simon);
		panther3 = new CPanther(921, 40, -1, simon);
		//objects.push_back(panther3);
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
