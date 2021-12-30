#include "TileSet.h"
#include "Game.h"
#include "MapData.h"

CTileSet::CTileSet(int firstgid, Vec2 tileSize, int tileCount, int columns, string imgPath)
{
	this->first_gid = firstgid;
	this->tile_size = Vec2(tileSize.x, tileSize.y);
	this->number_of_tiles = tileCount;
	this->columns = columns;
	this->texture = CGame::GetInstance()->LoadTexture(ToLPCWSTR(imgPath));
}

CTileSet::CTileSet(TiXmlElement* data, string xmlPath)
{
	data->QueryIntAttribute("firstgid", &this->first_gid);
	data->QueryFloatAttribute("tilewidth", &this->tile_size.x);
	data->QueryFloatAttribute("tileheight", &this->tile_size.y);
	data->QueryIntAttribute("tilecount", &this->number_of_tiles);
	data->QueryIntAttribute("columns", &this->columns);

	TiXmlElement* imgDom = data->FirstChildElement("image");
	string imgPath = xmlPath + "/" + imgDom->Attribute("source");
	this->texture = CGame::GetInstance()->LoadTexture(ToLPCWSTR(imgPath));
}

int CTileSet::GetFirstGID()
{
	return first_gid;
}

void CTileSet::Draw(int gid, float x, float y)
{
	x += tile_size.x / 2;
	y += tile_size.y / 2;

	RECT r;
	r.top = (LONG)((gid - first_gid) / columns) * (LONG)tile_size.y;
	r.left = (LONG)((gid - first_gid) % columns) * (LONG)tile_size.x;
	r.bottom = (LONG)r.top + (LONG)tile_size.y;
	r.right = (LONG)r.left + (LONG)tile_size.x;
	D3DXVECTOR3 pivot = { 0, 0, 0 };
	Transformation trans;
	CGame::GetInstance()->Draw(x, y, pivot, texture, r, trans, 1.0f);
}

CTileSet::~CTileSet()
{
	delete texture;
}
