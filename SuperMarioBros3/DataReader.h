#pragma once
#include "Utils.h"
#include <any>
#include <unordered_map>
#include <memory>

class DataReader
{
	string tag_name;
	unordered_map<string, any> contents;
public:
	DataReader(string tagName);

	bool HasNoTag();

	bool HasKey(string tagName);

	void RemoveTag(string name);

	bool GetBool(string tagName, bool default_val = false);
	void SetBool(string tagName, bool value);

	int GetInt(string tagName, int default_val = 0);
	void SetInt(string tagName, int value);

	long GetLong(string tagName, long default_val = 0);
	void SetLong(string tagName, long value);

	double GetDouble(string tagName, double default_val = 0);
	void SetDouble(string tagName, double value);

	float GetFloat(string tagName, float default_val = 0);
	void SetFloat(string tagName, float value);

	string GetString(string tagName, string default_val = "");
	void SetString(string tagName, string value);

	DataReader* GetDataTag(string tagName, DataReader* default_val = nullptr);
	void SetDataTag(DataReader* value);
};

