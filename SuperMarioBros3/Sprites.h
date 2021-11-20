#pragma once
#include "Utils.h"
#include "Texture.h"
#include "Textures.h"
#include "Sprite.h"

using namespace std;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPTEXTURE tex);
	LPSPRITE Get(string id);
	void Clear();
	virtual void Import(const char* filePath);
	static CSprites* GetInstance();
};

