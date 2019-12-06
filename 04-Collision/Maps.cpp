#include "Maps.h"


CMap::CMap(int texId, LPCSTR filePath, D3DCOLOR color)
{
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	CTextures::GetInstance()->Add(texId, filePath, color);

	tex = CTextures::GetInstance()->Get(texId);
}

void CMap::ReadMapTXT(LPCSTR filePath)
{
	ifstream inp(filePath, ios::in);
	inp >> rowMap >> columnMap >> rowTileSet >> columnTileSet >> frameWidth >> frameHeight >> drawPositionX >> drawPositionY;
	for (int i = 0; i < rowMap; i++)
		for (int j = 0; j < columnMap; j++)
		{
			inp >> tileMap[i][j];
		}
	inp.close();
}

void CMap::LoadTile() {

	for (int i = 0; i < rowTileSet; i++)
	{
		for (int j = 0; j < columnTileSet; j++)
		{
			int left = j * frameWidth;
			int top = i * frameHeight;
			int right = left + frameWidth;
			int bottom = top + frameHeight;
			LPTILE tile = new CTile(left, top, right, bottom, tex);
			tiles.push_back(tile);
		}
	}
}

void CMap::Render() {
	float cx = CGame::GetInstance()->GetCamPos_x();
	int beginColumn = cx;
	int endColumn = cx + SCREEN_WIDTH / frameWidth + 1; //SCREEN_WIDTH
	for (int i = 0; i < rowMap; i++) {
		for (int j = 0; j < columnMap; j++) {
			DebugOut(L"\ntiles: %d", tileMap[i][j]);
			tiles[tileMap[i][j]]->Draw(j*frameWidth + drawPositionX, i*frameHeight + drawPositionY);
		}
	}
};

int CMap::getMapWidth() {
	return columnMap * frameWidth;
};
int CMap::getMapHeight() {
	return rowMap * frameHeight;
};



CMaps* CMaps::__instance = NULL;

CMaps* CMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CMaps();
	return __instance;
}

void CMaps::Add(int id, LPMAP scene)
{
	maps[id] = scene;
}

LPMAP CMaps::Get(int id)
{
	return maps[id];
}