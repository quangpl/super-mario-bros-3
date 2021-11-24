#pragma once
#include "Utils.h"
#include "TileSet.h"
#include "Layer.h"
#include "SceneManager.h"
#include "Game.h"
#include "PlayScene.h"
#include "Camera.h"

class CGameMap
{
	int width;
	int height;
	int tile_width;
	int tile_height;

	D3DXCOLOR backgroundColor = D3DXCOLOR(181, 235, 242, 255);

	Camera* camera;

	CTileSet* tileSet;

	vector<CLayer*> layers;
	vector<CLayer*> ptr_layers;

public:
	CGameMap();

	virtual Camera* GetCamera() { return this->camera; }

	virtual void SetCamera(Camera* camera) { this->camera = camera; }

	virtual void AddLayer(CLayer* layer);

	Vec2 GetBoundingBox()
	{
		return Vec2((float)this->width * (float)tile_width, (float)this->height * (float)tile_height);
	}
	virtual void Render();
	static CGameMap* FromTMX(string filePath);
	~CGameMap();
};

typedef CGameMap* GameMap;

