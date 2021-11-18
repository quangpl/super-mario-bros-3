#include "MapData.h"

MapData::MapData()
{
}

MapData::MapData(TiXmlElement* data)
{
	if (data == nullptr) return;
	for (TiXmlElement* prop = data->FirstChildElement("property"); prop != nullptr; prop = prop->NextSiblingElement("property")) {
		string type = "text";
		if (prop->Attribute("type")) {
			type = prop->Attribute("type");
		}

		if (type.compare("text") == 0) {
			string name = prop->Attribute("name");
			string value = prop->Attribute("value");
			storage->SetString(name, value);
		}

		if (type.compare("bool") == 0) {
			string name = prop->Attribute("name");
			bool value = false;
			prop->QueryBoolAttribute("value", &value);
			storage->SetBool(name, value);
		}

		if (type.compare("int") == 0) {
			string name = prop->Attribute("name");
			int value = 0;
			prop->QueryIntAttribute("value", &value);
			storage->SetInt(name, value);
		}

		if (type.compare("float") == 0) {
			string name = prop->Attribute("name");
			float value = 0.0f;
			prop->QueryFloatAttribute("value", &value);
			storage->SetFloat(name, value);
		}
	}
}

bool MapData::HasProperty(string name)
{
	return storage->HasKey(name);
}

string MapData::GetText(string name, string def)
{
	return storage->GetString(name, def);
}

bool MapData::GetBool(string name, bool def)
{
	return storage->GetBool(name, def);
}

int MapData::GetInt(string name, int def)
{
	return storage->GetInt(name, def);
}

float MapData::GetFloat(string name, float def)
{
	return storage->GetFloat(name, def);
}
