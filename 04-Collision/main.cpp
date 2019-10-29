/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "Goomba.h"
#include "Candle.h"


#include "Map.h"
#include "Constants.h"

CGame *game;
CCandle* candle;
CSimon *simon;
Map* map1;

vector<CGameObject*> objects;

vector<LPGAMEOBJECT> coObjects;
vector<LPGAMEOBJECT> coGroundObjects;
vector<LPGAMEOBJECT> coPlayerObject;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)   //short event
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->GetState() != SIMON_STATE_SIT) {
			simon->SetState(SIMON_STATE_JUMP);
		}
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetLevel(SIMON_LEVEL);
		simon->SetPosition(50.0f,0.0f);
		simon->SetSpeed(0, 0);
		break;
	}
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)   //short event
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		simon->SetState(SIMON_STATE_SIT_RELEASE);
		break;
	}

}


void CSampleKeyHander::KeyState(BYTE *states)   //long event
{
	// disable control key when SIMON die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT)&&simon->GetState() != SIMON_STATE_SIT)
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT) && simon->GetState() != SIMON_STATE_SIT)
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
	if (game->IsKeyDown(DIK_DOWN)) {
		simon->SetState(SIMON_STATE_SIT);
		cout << "Sit" << endl;
	}
	
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and SIMON object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MAP, "textures\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, "Resources\\simon\\simon.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));

	
	
	map1 = new Map(ID_TEX_MAP, "textures\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
	map1->ReadMapTXT("textures\\Map1.txt");
	map1->LoadTile();

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);




	// Simon
	sprites->Add(10001, 163, 41, 180, 71, texSimon);		// idle right

	sprites->Add(10002, 205, 40, 217, 70, texSimon);		// walk right
	sprites->Add(10003, 244, 41, 259, 70, texSimon);

	sprites->Add(10011, 123, 40, 140, 71, texSimon);		// idle left
	sprites->Add(10012, 86, 41, 98, 71, texSimon);		// walk left
	sprites->Add(10013, 44, 41, 60, 70, texSimon);

	sprites->Add(10099, 35, 8, 68, 22, texSimon);		// die left
	sprites->Add(10098, 235, 8, 268, 22, texSimon);		// die right

	sprites->Add(10199, 3, 44, 19, 67, texSimon);		// jump left
	sprites->Add(10198, 283, 43, 300, 66, texSimon);		// jump right


	sprites->Add(10299, 4,44, 20, 67, texSimon);		// sit left
	sprites->Add(10298, 283, 44, 300, 66, texSimon);		// sit right

	// Simon transparent

	sprites->Add(100011, 163, 641, 180, 670, texSimon);		// idle right
	sprites->Add(100021, 205, 641, 217, 670, texSimon);		// walk right
	sprites->Add(100031, 244, 641, 259, 670, texSimon);

	sprites->Add(100111, 123, 641, 140, 670, texSimon);		// idle left
	sprites->Add(100121, 85, 641, 98, 670, texSimon);		// walk left
	sprites->Add(100131, 44, 641, 60, 670, texSimon);


	sprites->Add(100991, 4, 644, 20, 667, texSimon);		// sit left
	sprites->Add(100981, 283, 644, 300, 665, texSimon);		// sit right
	
															
															
															// Candle 
	sprites->Add(100211, 48, 26, 64, 56, texCandle);		// candle first state
	sprites->Add(100212, 75, 26, 91, 56, texCandle);		// candle second state


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 245, 420, 255, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	LPANIMATION ani;

	ani = new CAnimation(100);	// idle right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// jump left
	ani->Add(10199);
	animations->Add(700, ani);

	ani = new CAnimation(100);	// jump right
	ani->Add(10198);
	animations->Add(701, ani);

	ani = new CAnimation(100);	// sit left
	ani->Add(10299);
	animations->Add(800, ani);

	ani = new CAnimation(100);	// sit right
	ani->Add(10298);
	animations->Add(801, ani);



	ani = new CAnimation(100);	// walk right 
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);	// // walk left 
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);



	ani = new CAnimation(100);		// Simon die left
	ani->Add(10099);
	animations->Add(599, ani);

	ani = new CAnimation(100);		// Simon die right
	ani->Add(10098);
	animations->Add(598, ani);

	

	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);


	ani = new CAnimation(100);	// candle firing
	ani->Add(100211);
	ani->Add(100212);
	animations->Add(900, ani);


	
	for (int i = 1; i <= 5; i++) {
		candle = new CCandle();
		candle->AddAnimation(900);
		candle->SetPosition(i * 130, 167);
		objects.push_back(candle);
	}

	simon = new CSimon();
	simon->AddAnimation(400);		// idle right 
	simon->AddAnimation(401);		// idle left big
	simon->AddAnimation(599);		// die left
	simon->AddAnimation(598);		// die right
	simon->AddAnimation(500);		// walk right big
	simon->AddAnimation(501);		// walk left big

	

	simon->AddAnimation(700);		// jump left
	simon->AddAnimation(701);		// jump right

	simon->AddAnimation(800);		// sit left
	simon->AddAnimation(801);		// sit right


	simon->SetPosition(50.0f, 0);
	objects.push_back(simon);



	for (int i = 0; i < 48; i++)
	{
		float l, t, r, b;
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*16.0f, SCREEN_HEIGHT-45);
		objects.push_back(brick);
	}

	


}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;


	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getType() == TYPE_OBJECT_PLAYER || objects[i]->getType() == TYPE_OBJECT_BACKGROUND) {
			coObjects.push_back(objects[i]);
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		
			objects[i]->Update(dt, &coObjects);
		
	}


	// Update camera to follow SIMON
	float cx, cy;
	simon->GetPosition(cx, cy);

	
	
	//Khoảng cách để Simon vô giữa màn hình
	if (cx >= SCREEN_WIDTH / 2) { 
		cx -= SCREEN_WIDTH / 2;
	}
	else {
		cx = 0;
	}

	if (cy > SCREEN_HEIGHT) {
		cy -= SCREEN_HEIGHT / 2;
	}
	else {
		cy = 10.0f;
	}

	CGame::GetInstance()->SetCamPos(cx, cy); //Khoảng cách để Simon đứng ngay giữa màn hình không bị lệch 

	
}


/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		map1->Render();
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = CGame::GetInstance();
	game->Init(hWnd);


	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	showConsole();
	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	
	Run();
	
	return 0;
}