#include "Hud.h"
#include "HubObjects.h"
#include "Game.h"

Hud::Hud(string tmxPath, Vec2 pos, Vec2 size)
{
	powerMeter = new PowerMeter();

	this->LoadFromTmx(tmxPath);
}

void Hud::Update(DWORD dt)
{
	powerMeter->Update(dt);
}

void Hud::Render()
{
	powerMeter->Render();
}


void Hud::LoadFromTmx(string tmxPath)
{
	TiXmlDocument doc(tmxPath.c_str());

	if (!doc.LoadFile()) {
		DebugOut(L"Cannot load hud config file.\n");
		return;
	}

	TiXmlElement* root = doc.RootElement();

	for (TiXmlElement* group = root->FirstChildElement("objectgroup"); group != nullptr; group = group->NextSiblingElement("objectgroup"))
	{
		for (TiXmlElement* node = group->FirstChildElement("object"); node != nullptr; node = node->NextSiblingElement("object"))
		{
			Vec2 fixPos;
			Vec2 size = VECTOR_0;
			node->QueryFloatAttribute("x", &fixPos.x);
			node->QueryFloatAttribute("y", &fixPos.y);
			node->QueryFloatAttribute("width", &size.x);
			node->QueryFloatAttribute("height", &size.y);

			if (!node->Attribute("type")) continue;

			if (strcmp(node->Attribute("type"), HudElement::PMeter.ToString().c_str()) == 0) {
				powerMeter->position = fixPos;
				powerMeter->size = size;
				continue;
			}
		}
	}
}
