#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "debug.h"
#include "Weapon.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "tinyxml.h"
#include "Simon.h"
#include "Brick.h"
#include "Goomba.h"
#include "SceneGame.h"
#include "Scenes.h"
#include "Candles.h"
#include <iostream>
#include <istream>
#include <string>
#include "Map.h"
#include "Items.h"
#include <sstream> 
#include "Constants.h"

using namespace std;
CScenes* scenes = CScenes::GetInstance();
CSceneGame* sceneGame = CSceneGame::GetInstance();

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)   //short event
{
	CGame* game;
	CCandles* candles = CCandles::GetInstance();
	CItems* items = CItems::GetInstance();
	CWeapon* weapon = CWeapon::GetInstance();
	CSimon* simon = CSimon::GetInstance();
	if (simon->getFreeze()) {
		return;
	}
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetLevel(SIMON_LEVEL);
		simon->SetPosition(50.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	}

}

void CSampleKeyHander::OnKeyUp(int KeyCode)   //short event
{
	CGame* game;
	CCandles* candles = CCandles::GetInstance();
	CItems* items = CItems::GetInstance();
	CWeapon* weapon = CWeapon::GetInstance();
	CSimon* simon = CSimon::GetInstance();
	if (simon->getFreeze()) {
		return;
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		simon->SetState(SIMON_STATE_SIT_RELEASE);
		break;
	case DIK_Z:
		simon->SetState(SIMON_STATE_HIT_RELEASE);
		//weapon->SetState(WEAPON_STATE_NO_WEAPON);
		break;
	case DIK_X:
		simon->SetState(SIMON_STATE_HIT_RELEASE);
		break;
	default:
		break;
	}

}


void CSampleKeyHander::KeyState(BYTE* states)   //long event
{
	CGame* game = CGame::GetInstance();
	CCandles* candles = CCandles::GetInstance();
	CItems* items = CItems::GetInstance();
	CWeapon* weapon = CWeapon::GetInstance();
	CSimon* simon = CSimon::GetInstance();
	//Khóa phím khi simon đóng băng
	if (simon->getFreeze()) {
		return;
	}
	// disable control key when SIMON die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->GetState() == SIMON_STATE_HIT) {
			weapon->SetState(WEAPON_STATE_ROPE);
			simon->SetState(SIMON_STATE_HIT);
		}
		simon->SetState(SIMON_STATE_SIT);
	}

	if (game->IsKeyDown(DIK_Z))
	{
		weapon->SetState(WEAPON_STATE_ROPE);
		simon->SetState(SIMON_STATE_HIT);
	}
	if (game->IsKeyDown(DIK_X) && weapon->getHasDagger() && !weapon->isShow())
	{
		//weapon->show();
		weapon->setTypeWeapon(WEAPON_TYPE_DAGGER);
		weapon->SetState(WEAPON_STATE_DAGGER);
		simon->SetState(SIMON_STATE_HIT);
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
	scenes->Get(SCENE_GAME_ID)->LoadResources();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	scenes->Get(SCENE_GAME_ID)->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	CGame* game = CGame::GetInstance();
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		scenes->Get(SCENE_GAME_ID)->Render();
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

			CGame::GetInstance()->ProcessKeyboard();
			
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
	CGame* game;

	game = CGame::GetInstance();
	game->Init(hWnd);

	scenes->Add(SCENE_GAME_ID, sceneGame);
	keyHandler = new CSampleKeyHander();
	scenes->Add(SCENE_GAME_ID, sceneGame);
	game->InitKeyboard(keyHandler);
	//showConsole();
	
	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	
	Run();
	
	return 0;
}