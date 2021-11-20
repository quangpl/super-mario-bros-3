#define _CRT_SECURE_NO_WARNINGS
#include "GameMap.h"
#include "ObjectTypeData.h"
#include "MapData.h"


CGameMap::CGameMap()
{
	this->width = this->height = this->tile_height = this->tile_width = 0;
}

void CGameMap::AddLayer(shared_ptr<CLayer> layer)
{
	this->layers.push_back(layer);
}


void CGameMap::Render()
{
	int col = (int)(this->camera->position.x / tile_width);
	int row = (int)(this->camera->position.y / tile_height);

	if (col > 0) col--;
	if (row > 0) row--;

	Vec2 camSize = Vec2(this->camera->GetCamSize().x / tile_width, this->camera->GetCamSize().y / tile_height);
	Vec2 camPos = camera->position;

	int firstGID = tileSet->GetFirstGID();

	for (CLayer* layer : ptr_layers) {

		int** tiles = layer->GetTiles();
		for (int i = col; i < camSize.x + col + 2; i++) {
			if (i < 0 || i >= width) continue;

			for (int j = row; j < camSize.y + row + 2; j++) {
				if (j < 0 || j >= height) continue;

				int id = tiles[i][j];
				if (id < firstGID) continue;

				int x = i * tile_width - camPos.x;
				int y = j * tile_height - camPos.y;

				tileSet->Draw(id, x, y);
			}
		}
	}
}

shared_ptr<CGameMap> CGameMap::FromTMX(string filePath)
{
	TiXmlDocument doc(filePath.c_str());

	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		shared_ptr<CGameMap> gameMap = make_shared<CGameMap>();

		root->QueryIntAttribute("width", &gameMap->width);
		root->QueryIntAttribute("height", &gameMap->height);
		root->QueryIntAttribute("tilewidth", &gameMap->tile_width);
		root->QueryIntAttribute("tileheight", &gameMap->tile_height);

		if (root->Attribute("backgroundcolor")) {
			string hexColor = root->Attribute("backgroundcolor");
			hexColor.replace(0, 1, "");
			unsigned int hex = stoul(hexColor, nullptr, 16);
			int a = (hex >> 24) & 255 | 255 & (hexColor.length() <= 6 ? 0xff : 0x00);
			gameMap->backgroundColor = D3DXCOLOR((hex >> 16) & 255, (hex >> 8) & 255, hex & 255, a);
		}

		//Load custom properties
		TiXmlElement* properties = root->FirstChildElement("properties");
		MapData mapProps = MapData(properties);

		//Load tileset
		char mapDir[_MAX_DIR];
		_splitpath(filePath.c_str(), NULL, mapDir, NULL, NULL);
		gameMap->tileSet = make_shared<CTileSet>(root->FirstChildElement("tileset"), mapDir);

		//Load layer
		for (TiXmlElement* node = root->FirstChildElement("layer"); node != nullptr; node = node->NextSiblingElement("layer")) {
			shared_ptr<CLayer> layer = make_shared<CLayer>(node, gameMap);
			gameMap->AddLayer(layer);
			gameMap->ptr_layers.push_back(&*layer);
		}

		for (TiXmlElement* node = root->FirstChildElement("objectgroup"); node != nullptr; node = node->NextSiblingElement("objectgroup")) {
			for (TiXmlElement* object = node->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {
				try {
					Vec2 fixPos;
					Vec2 size = VECTOR_0;
					object->QueryFloatAttribute("x", &fixPos.x);
					object->QueryFloatAttribute("y", &fixPos.y);
					object->QueryFloatAttribute("width", &size.x);
					object->QueryFloatAttribute("height", &size.y);
					const char* type = object->Attribute("type");

					TiXmlElement* nodeProperties = object->FirstChildElement("properties");
					MapData props = MapData(nodeProperties);
					shared_ptr<CScene> activeScene = SceneManager::GetInstance()->GetActiveScene();
					activeScene->LoadObjects(type, fixPos, size, props);
				}
				catch (exception) {}
			}
		}

		doc.Clear();

		DebugOut(L"Load game map success.\n");

		return gameMap;
	}
	throw "Load map fail";
}
CGameMap::~CGameMap()
{
	ptr_layers.clear();
	layers.clear();
}
