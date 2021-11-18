#pragma once
#include "Utils.h"
#include "Texture.h"

class CTileSet
{
	// the starting id of tile on Tiled 
	int first_gid;

	Vec2 tile_size;

	int number_of_tiles;
	int columns;

	LPTEXTURE texture;

public:
	CTileSet(int firstgid, Vec2 tileSize, int tileCount, int columns, string imgPath);
	CTileSet(TiXmlElement* data, string xmlPath);

	int GetFirstGID();

	void Draw(int gid, float x, float y);

	~CTileSet();
};

typedef CTileSet* TileSet;