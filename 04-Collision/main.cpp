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
#include "Maps.h"
#include "Items.h"
#include <sstream> 
#include "Constants.h"
#include "Keyboard.h"

using namespace std;
CScenes* scenes = CScenes::GetInstance();

CSceneGame* sceneGame = CSceneGame::GetInstance();
CSampleKeyHander* keyHandler = new CSampleKeyHander();
D3DCOLOR createBlinkColor() {
	int randomInt = 1 + rand() % (2);
	if (randomInt % 2 == 0) {
		return  D3DCOLOR_XRGB(0, 0, 0);
	}
	else {
		return  D3DCOLOR_XRGB(255, 255, 255);
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
	CTextures* textures = CTextures::GetInstance();

	//textures->Add(ID_TEX_MAP_2, "Map\\tileset_map2.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_MAP_1, "Map\\tileset_map1.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_BBOX, "textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_SIMON, "textures\\TexturesV4.png", D3DCOLOR_XRGB(34, 177, 76));
	//textures->Add(ID_TEX_CANDLE, "textures\\object.png", D3DCOLOR_XRGB(34, 177, 76));
	//textures->Add(ID_TEX_ITEM, "textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));
	//textures->Add(ID_TEX_ENEMY, "textures\\enemy.png", D3DCOLOR_XRGB(96, 68, 106));
	
	ifstream fileTextures("textures\\Textures.txt", ios::in);
	int texId, nTexture, R, G, B;
	string texFilePath;
	fileTextures >> nTexture;
	for (int i = 0; i < nTexture; i++)
	{
		fileTextures >> texId >> texFilePath >> R >> G >> B;
		textures->Add(texId, texFilePath.c_str(), D3DCOLOR_XRGB(R, G, B));
	}
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
		if (game->getIsBlinkScene()) {
			d3ddv->ColorFill(bb, NULL, createBlinkColor());
		}
		else {
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		}
		
		//tao ao giac - cross
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
	
	scenes->Add(SCENE_GAME_ID, sceneGame);
	scenes->Get(SCENE_GAME_ID)->setStage(1);
	CGame::GetInstance()->Init(hWnd);
	
	CGame::GetInstance()->InitKeyboard(keyHandler);
	
	showConsole();
	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	
	Run();
	
	return 0;
}