#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"

#include "Game.h"
#include "Tile.h"
#include <fstream>
#include "Textures.h"
#include "debug.h"

using namespace std;

class Map
{
	int frameWidth, frameHeight;

	int columnTileSet, rowTileSet, columnMap, rowMap;

	int drawPositionX, drawPositionY;
	int tileMap[TILE_MAP_SIZE][TILE_MAP_SIZE];

	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	vector<LPTILE> tiles;
public:

	Map(int texId, LPCSTR filePath, D3DCOLOR color);

	void ReadMapTXT(LPCSTR filePath);

	void LoadTile();

	void SetMapPosition(int offsetX, int offsetY);

	void Render();
	int getMapWidth();
	int getMapHeight();

};

typedef Map * LPTILES;