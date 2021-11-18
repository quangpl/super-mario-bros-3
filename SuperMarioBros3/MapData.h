#pragma once
#include "Utils.h"
#include "DataReader.h"
#include <memory>
class MapData
{
public:
	MapData();
	MapData(TiXmlElement* data);

	virtual bool HasProperty(string name);

	virtual string GetText(string name, string def = "");
	virtual bool GetBool(string name, bool def = true);
	virtual int GetInt(string name, int def = 0);
	virtual float GetFloat(string name, float def = 0.0f);

protected:
	shared_ptr<DataReader> storage = make_shared<DataReader>("Root");
};

