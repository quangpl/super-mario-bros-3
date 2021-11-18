#include "DataReader.h"

DataReader::DataReader(string tagName)
{
	this->tag_name = tagName;
}

bool DataReader::HasNoTag()
{
	return contents.size() == 0;
}

bool DataReader::HasKey(string tagName)
{
	return contents.size() > 0 && contents.find(tagName) != contents.end();
}

void DataReader::RemoveTag(string name)
{
	contents.erase(name);
}

bool DataReader::GetBool(string tagName, bool default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<bool>(contents.at(tagName));
}

void DataReader::SetBool(string tagName, bool value)
{
	contents[tagName] = value;
}

int DataReader::GetInt(string tagName, int default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<int>(contents.at(tagName));
}

void DataReader::SetInt(string tagName, int value)
{
	contents[tagName] = value;
}

long DataReader::GetLong(string tagName, long default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<long>(contents.at(tagName));
}

void DataReader::SetLong(string tagName, long value)
{
	contents[tagName] = value;
}

double DataReader::GetDouble(string tagName, double default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<double>(contents.at(tagName));
}

void DataReader::SetDouble(string tagName, double value)
{
	contents[tagName] = value;
}

float DataReader::GetFloat(string tagName, float default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<float>(contents.at(tagName));
}

void DataReader::SetFloat(string tagName, float value)
{
	contents[tagName] = value;
}

string DataReader::GetString(string tagName, string default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<string>(contents.at(tagName));
}

void DataReader::SetString(string tagName, string value)
{
	contents[tagName] = value;
}

shared_ptr<DataReader> DataReader::GetDataTag(string tagName, shared_ptr<DataReader> default_val)
{
	if (!HasKey(tagName)) return default_val;
	return any_cast<shared_ptr<DataReader>>(contents.at(tagName));
}

void DataReader::SetDataTag(shared_ptr<DataReader> value)
{
	if (value == nullptr)
		throw "Value cannot be null!!!";
	if (&(*value) == this)
		throw "Loop detected!!!";
	if (&(*value->GetDataTag(tag_name)) == this)
		throw "Loop detected!!!";

	contents[value->tag_name] = value;
}
