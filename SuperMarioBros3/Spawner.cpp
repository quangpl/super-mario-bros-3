#include "Spawner.h"

Spawner::Spawner()
{
	spawnTimer.Reset();
	spawnTimer.Stop();
}

CGameObject* Spawner::GetSpawnObject()
{
	if (type.compare(ObjectTypeData::Goomba.ToString()) == 0) {
		return (CGoomba::Create(position));
	}
	if (type.compare(ObjectTypeData::RedGoomba.ToString()) == 0) {
		return (CRedWingGoomba::Create(position));
	}
	if (type.compare(ObjectTypeData::RedGoomba.ToString()) == 0) {
		return (CRedWingGoomba::Create(position));
	}
	if (type.compare(ObjectTypeData::RedKoopas.ToString()) == 0) {
		return (CKoopas::Create(position));
	}
	if (type.compare(ObjectTypeData::Piranha.ToString()) == 0) {
		return (new Piranha(position));
	}
	else {
		return NULL;
	}
}

void Spawner::Spawn()
{
	if (entities.size() == spawnLimit) return;
	CMario* mario = CMario::GetInstance();
	CGameObject* obj = GetSpawnObject();
	if (obj == NULL) {
		return;
	}
	if (mario->GetPosition().x < position.x) {
		obj->SetNx(-1);
		obj->SetVelocityX(-abs(obj->GetSpeed().x));
	}
	else {
		obj->SetNx(1);
		obj->SetVelocityX(abs(obj->GetSpeed().x));
	}

	entities.push_back(obj);
	SceneManager::GetInstance()->GetActiveScene()->AddObject(obj);
	respawnLimit--;
	spawnTimer.Restart();
}

void Spawner::Render()
{
}



void Spawner::Update()
{
	if (!autoSpawn) return;
	Spawn();
}


RectBox Spawner::GetBoundingBox()
{
	this->bounding_box.left = position.x - size.x / 2;
	this->bounding_box.top = position.y - size.y / 2;
	this->bounding_box.right = position.x - size.x / 2;
	this->bounding_box.bottom = position.x - size.x / 2;
	return this->bounding_box;
}

bool Spawner::CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy)
{
	return true;
}

void Spawner::OnGoingToCamera()
{
	this->Spawn();
}


Spawner* Spawner::Create(Vec2 fixedPos, MapData properties)
{
	Spawner* spawner = new Spawner();
	spawner->SetPosition(Vec2(fixedPos.x, fixedPos.y));

	spawner->autoSpawn = properties.GetBool("AutoSpawn", false);
	spawner->respawnLimit = properties.GetInt("RespawnLimit", 1);
	spawner->spawnDelay = properties.GetInt("SpawnDelay", 500);
	spawner->type = properties.GetText("EntityType", "Goomba");
	spawner->spawnLimit = properties.GetInt("SpawnLimit", 1);
	spawner->respawnLimit += spawner->spawnLimit;
	spawner->props = properties;

	return spawner;
}