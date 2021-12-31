#pragma once
#include "PlayScene.h"


using namespace std;

CPlayScene::CPlayScene()
{
	this->player = CMario::GetInstance();
	this->player->SetPlayerState(new SmallMario());
	key_handler = new CSampleKeyHandler(this);
	gameMap = NULL;
}


void CPlayScene::OnKeyDown(int KeyCode)
{
	if (!player)
		return;
	player->GetPlayerState()->OnKeyDown(KeyCode);

	// FIXME: Just for development
	switch (KeyCode)
	{
	case DIK_1:
		player->position.y = player->position.y - 50;
		player->SetPlayerState(new SmallMario());
		break;
	case DIK_2:
		player->position.y = player->position.y - 50;
		player->SetPlayerState(new BigMario());
		break;
	case DIK_3:
		player->position.y = player->position.y - 50;
		player->SetPlayerState(new RaccoonMario());
		break;
	case DIK_X:
		//player->SetPosition(Vec2{ 6000,700 });
		player->SetPosition(Vec2{ 1692,880 });
		break;
	case DIK_Y:
		player->SetPosition(Vec2{ 6000,700 });
		break;
	case DIK_T:
		player->SetPosition(Vec2{ 6772,400 });
		break;
	default:
		break;
	}
}
void CPlayScene::KeyStateHandler() {

}

void CPlayScene::OnKeyUp(int KeyCode)
{
	if (!player)
		return;
	player->GetPlayerState()->OnKeyUp(KeyCode);
}



void CPlayScene::LoadMap() {
	TiXmlDocument doc(this->data_path.c_str());
	if (!doc.LoadFile()) {
		DebugOut(L"Get scene data failed. File: %s\n", ToLPCWSTR(this->data_path));
		return;
	}

	TiXmlElement* root = doc.RootElement();

	string mapPath = root->FirstChildElement("TmxMap")->Attribute("path");
	this->camera = new Camera(this->camSize);
	this->camera->LoadFromTMX(root->FirstChildElement("Camera"));
	this->camera->SetTrackingObject(this->player);

	this->gameMap = CGameMap::FromTMX(mapPath);
	this->gameMap->SetCamera(camera);

	Vec2 boundingMap = gameMap->GetBoundingBox();
	this->player->moveLimitaion = RectBox(0, -boundingMap.y, boundingMap.x, boundingMap.y);

	doc.Clear();

}

void CPlayScene::LoadObjects(const char* type, Vec2 position, Vec2 size, MapData& data) {
	if (strcmp(type, "SpawnPoint") == 0) {
		this->player->SetPosition(position);
	}
	/*if (strcmp(type, ObjectTypeData::Goomba.ToString().c_str()) == 0) {
		AddObject(CGoomba::Create(position));
	}*/
	/*if (strcmp(type, ObjectTypeData::RedGoomba.ToString().c_str()) == 0) {
		AddObject(CRedWingGoomba::Create(position), data);
	}*/
	if (strcmp(type, ObjectTypeData::SolidBlock.ToString().c_str()) == 0) {
		AddObject(CGround::Create(position, size, true), data);
	}
	if (strcmp(type, ObjectTypeData::Venus.ToString().c_str()) == 0) {
		AddObject(new Venus(position, VenusType::GreenVenus));
	}
	if (strcmp(type, ObjectTypeData::RedVenus.ToString().c_str()) == 0) {
		AddObject(new Venus(position, VenusType::RedVenus));
	}
	/*if (strcmp(type, ObjectTypeData::Koopas.ToString().c_str()) == 0) {
		AddObject(GreenKoopas::Create(position, false), data);
	}
	if (strcmp(type, ObjectTypeData::KoopasJumping.ToString().c_str()) == 0) {
		AddObject(GreenKoopas::Create(position, true), data);
	}*/
	/*if (strcmp(type, ObjectTypeData::CommandPoint.ToString().c_str()) == 0) {
		AddObject(CCommandPoint::Create(position, data), data);
	}*/
	if (strcmp(type, ObjectTypeData::GhostBlock.ToString().c_str()) == 0) {
		AddObject(CGround::Create(position, size, false), data);
	}
	if (strcmp(type, ObjectTypeData::QuestionBlock.ToString().c_str()) == 0) {
		AddObject(CBrick::Create(position, data), data);
	}
	if (strcmp(type, ObjectTypeData::Brick.ToString().c_str()) == 0) {
		AddObject(CCoin::Create(position, COIN_STATE_BRICK), data);
	}
	if (strcmp(type, ObjectTypeData::Coin.ToString().c_str()) == 0) {
		AddObject(CCoin::Create(position, COIN_STATE_NORMAL_COIN), data);
	}
	if (strcmp(type, ObjectTypeData::Piranha.ToString().c_str()) == 0) {
		AddObject(new Piranha(position));
	}
	/*if (strcmp(type, ObjectTypeData::Koopas.ToString().c_str()) == 0) {
		AddObject(CKoopas::Create(position), data);
	}*/
	if (strcmp(type, ObjectTypeData::BeginPortal.ToString().c_str()) == 0) {
		AddObject(new BeginPortal(position, size, data), data);
	}
	if (strcmp(type, ObjectTypeData::EndPortal.ToString().c_str()) == 0) {
		AddObject(new EndPortal(position, size, data), data);
	}
	if (strcmp(type, ObjectTypeData::Pipe.ToString().c_str()) == 0) {
		AddObject(CPipe::Create(position, size, data), data);
	}
	if (strcmp(type, ObjectTypeData::Spawner.ToString().c_str()) == 0) {
		AddObject(Spawner::Create(position, data), data);
	}
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n");
	LoadMap();
	CGame::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	DebugOut(L"[INFO] Done loading scene  %s\n");
}

void CPlayScene::Update(DWORD dt)
{
	this->KeyStateHandler();
	this->camera->Update();
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
		if (!this->camera->IsInCamera(objects[i])) {
			if (objects[i]->is_in_camera) {
				objects[i]->OnLeavingCamera();
			}
			objects[i]->is_in_camera = false;
		}
		else {
			if (!objects[i]->is_in_camera) {
				objects[i]->OnGoingToCamera();
			}
			objects[i]->is_in_camera = true;
		}
	}
	player->Update(dt, &coObjects);
	coObjects.push_back(player);
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	for (auto x : CEffectManager::GetInstance()->GetAll())
	{
		LPEFFECT effect = x.second;
		effect->Update(dt);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	//if (player == NULL) return;
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	sort(objects.begin(), objects.end(), [](CGameObject* firstObject, CGameObject* secondObject) {
		return firstObject->zIndex < secondObject->zIndex;
		});

	gameMap->Render();
	if (!player->IsDeleted()) {
		player->Render();
	}
	for (auto x : CEffectManager::GetInstance()->GetAll())
	{
		LPEFFECT effect = x.second;
		effect->Render();
	}
	for (int i = 0; i < (int)objects.size(); i++) {
		if (objects[i]->IsDeleted()) {
			continue;
		}
		objects[i]->Render();
	}

}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	/*for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}*/
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	/*for (int i = 0; i < objects.size(); i++)
		delete objects[i];*/

	objects.clear();
	//player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	//vector<LPGAMEOBJECT>::iterator it;
	//for (it = objects.begin(); it != objects.end(); it++)
	//{
	//	LPGAMEOBJECT o = *it;
	//	if (o->IsDeleted())
	//	{
	//		delete o;
	//		*it = NULL;
	//	}
	//}

	//// NOTE: remove_if will swap all deleted items to the end of the vector
	//// then simply trim the vector, this is much more efficient than deleting individual items
	//objects.erase(
	//	std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
	//	objects.end());
}