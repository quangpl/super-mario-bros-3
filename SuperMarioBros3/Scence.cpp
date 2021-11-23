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

void CScene::AddObject(CGameObject* entity)
{
	objects.push_back(entity);
}

void CScene::AddObject(CGameObject* entity, MapData& data)
{
	objects.push_back(entity);
}