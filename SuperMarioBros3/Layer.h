#pragma once
#include "Utils.h"
#include <memory>
class CGameMap;

class CLayer
{
	int id;
	int visible;

	int width;
	int height;

	int** tiles;
public:
	CLayer();
	CLayer(TiXmlElement* data, CGameMap* map);

	bool Visible();

	int GetTileID(int x, int y);

	int** GetTiles();

	~CLayer();
};

typedef CLayer* Layer;
