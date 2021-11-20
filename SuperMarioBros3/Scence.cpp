#include "Scene.h"

void CScene::SetDataPath(string path) {
	TiXmlDocument doc(path.c_str());

	if (!doc.LoadFile()) {
		DebugOut(L"Cannot load scene data at path: %s\n", ToLPCWSTR(path));
		return;
	}
	DebugOut(L"Load scene data success. File: %s\n", ToLPCWSTR(path));
	doc.Clear();

	this->data_path = path;
}

void CScene::AddObject(shared_ptr<CGameObject> entity)
{
	objects[entity->GetID()] = entity;
}

void CScene::AddObject(shared_ptr<CGameObject> entity, MapData& data)
{
	objects[entity->GetID()] = entity;
}