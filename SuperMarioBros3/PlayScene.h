#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "TileMap.h"
#include "Goomba.h"
#include "Animations.h"
#include "Ground.h"
#include "Pipe.h"
#include "Utils.h"
#include "Koopas.h"
#include "MushRoom.h"
#include "ActivationPoint.h"
#include "EffectManager.h";
#include <memory>
#include "Camera.h"
#include "GameMap.h"

class CPlayScene: public CScene
{
	Vec2 camSize = Vec2(769, 579);
	shared_ptr<Camera> camera;
	shared_ptr<CGameMap> gameMap;
	string xml_path = "Resource/Scenes/World1-1.xml";
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void LoadMap();
	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

