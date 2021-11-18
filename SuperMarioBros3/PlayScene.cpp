#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Platform.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CSampleKeyHandler(this);
}


void CPlayScene::LoadMap() {
	TiXmlDocument doc(this->xml_path.c_str());

	if (!doc.LoadFile()) {
		DebugOut(L"Get scene data failed. File: %s\n", ToLPCWSTR(this->xml_path));
		return;
	}

	TiXmlElement* root = doc.RootElement();

	string mapPath = root->FirstChildElement("TmxMap")->Attribute("path");
	this->camera = make_shared<Camera>(camSize);
	this->camera->LoadFromTMX(root->FirstChildElement("Camera"));
	//this->camera->SetTracking(mario);

	this->gameMap = CGameMap::FromTMX(mapPath);
	this->gameMap->SetCamera(camera);

	//Vec2 mapBound = gameMap->GetBound();
	//this->mario->MovingBound = RectF(0, -mapBound.y, mapBound.x, mapBound.y);

	doc.Clear();

}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n");
	LoadMap();
	DebugOut(L"[INFO] Done loading scene  %s\n");
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	/*for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}*/
	/*for (auto x : CEffectManager::GetInstance()->GetAll())
	{
		LPEFFECT effect = x.second;
		effect->Update(dt);
	}*/
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	//if (player == NULL) return;
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	if (this->gameMap) {
		this->gameMap->Render();
	}
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	for (auto x : CEffectManager::GetInstance()->GetAll())
	{
		LPEFFECT effect = x.second;
		effect->Render();
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	//player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}