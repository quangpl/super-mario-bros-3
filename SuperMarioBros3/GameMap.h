#pragma once
#include "Utils.h"
#include "TileSet.h"
#include "Layer.h"
#include "Game.h"
#include "Camera.h"

class CGameMap
{
	int width;
	int height;
	int tile_width;
	int tile_height;

	D3DXCOLOR backgroundColor = D3DXCOLOR(181, 235, 242, 255);

	shared_ptr<Camera> camera;

	shared_ptr<CTileSet> tileSet;

	vector<shared_ptr<CLayer>> layers;
	vector<CLayer*> ptr_layers;

public:
	CGameMap();

	virtual shared_ptr<Camera> GetCamera() { return this->camera; }

	virtual void SetCamera(shared_ptr<Camera> camera) { this->camera = camera; }

	virtual void AddLayer(shared_ptr<CLayer> layer);

	virtual void Render();

	static shared_ptr<CGameMap> FromTMX(string filePath);
	~CGameMap();
};

typedef CGameMap* GameMap;

