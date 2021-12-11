#pragma once
#include "Game.h"
#include "Textures.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Animations.h"
#include "Ground.h"
#include "Pipe.h"
#include "MapData.h"
#include "Utils.h"
#include "Koopas.h"
#include "RedMushRoom.h"
#include "CommandPoint.h"
#include "RedWingGoomba.h"
#include "EffectManager.h";
#include "ObjectTypeData.h"
#include "GameMap.h"
#include "SampleKeyEventHandler.h"
#include "Spawner.h"
#include "BigMario.h"
#include "EffectManager.h"
#include "SmallMario.h"
#include "Coin.h"
#include "RaccoonMario.h"


class CPlayScene: public CScene
{	
	CGameMap* gameMap;
public: 
	CKeyEventHandler* key_handler;
	CMario* player = NULL;
	CPlayScene();

	virtual void Load();
	virtual void LoadObjects(const char* type, Vec2 fixedPos, Vec2 size, MapData& data);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	virtual void KeyStateHandler();
	CKeyEventHandler* GetKeyEventHandler() { return this->key_handler; }
	void LoadMap();
	void Clear();
	void PurgeDeletedObjects();


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

