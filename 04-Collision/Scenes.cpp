#include "Scenes.h"
#include "Game.h"
#include "debug.h"

CScenes* CScenes::__instance = NULL;

CScenes* CScenes::GetInstance()
{
	if (__instance == NULL) __instance = new CScenes();
	return __instance;
}

void CScenes::Add(int id, LPSCENE scene)
{
	scenes[id] = scene;
}

LPSCENE CScenes::Get(int id)
{
	return scenes[id];
}
