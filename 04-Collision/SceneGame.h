#pragma once
#include "Scenes.h"

class CSceneGame : public CScene
{
	static CSceneGame* __instance;
	int stage;
public:
	CSceneGame();
	~CSceneGame();

	void LoadResources();
	void setStage(int _stage) { this->stage = _stage; };
	int getStage(int _stage) { return this->stage; };
	void Update(DWORD dt);
	void Render();
	void Init(HWND hWnd);
	static CSceneGame* GetInstance();
};
