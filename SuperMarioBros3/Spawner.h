#pragma once
#include "GameObject.h"
#include "MapData.h"
#include "Goomba.h"
#include "StopWatch.h"
#include "ObjectTypeData.h"
#include "SceneManager.h"
#include "RedWingGoomba.h"
#include "Piranha.h"
#include "Venus.h"
#include "GreenKoopas.h"

class Spawner :
	public CGameObject
{
public:
	Spawner();

	virtual CGameObject* GetSpawnObject();

	virtual void Spawn();

	virtual void Update();

	virtual RectBox GetBoundingBox();
	virtual void Render() override;

	virtual void OnGoingToCamera();

	virtual bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);

	static Spawner* Create(Vec2 pos, MapData data);
	string type = "Goomba";

protected:
	Vec2 size = Vec2(1, 1);

	bool autoSpawn = false;

	vector<CGameObject*> entities;

	MapData props;


	int respawnLimit = 0;
	int spawnLimit = 0;

	long spawnDelay = 0;
	Stopwatch spawnTimer;
};

