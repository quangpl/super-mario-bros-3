#pragma once
#include "Utils.h"
#include "Animation.h"
#include "Sprite.h"

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);
	void Clear();
	void Import(const char* filePath);
	static CAnimations* GetInstance();
};
