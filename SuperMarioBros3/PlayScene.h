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
#include "MushRoom.h"
#include "ActivationPoint.h"
#include "EffectManager.h";
#include "ObjectTypeData.h"
#include "GameMap.h"
#include "SampleKeyEventHandler.h"

class CPlayScene: public CScene
{	
	CGameMap* gameMap;
public: 
	CGameObject* player = NULL;
	CPlayScene();

	virtual void Load();
	virtual void LoadObjects(const char* type, Vec2 fixedPos, Vec2 size, MapData& data);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void LoadMap();
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

