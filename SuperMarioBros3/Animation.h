#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"

using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	float playScale;
	Transformation* transform;

	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultFrameTime = 100);
	CAnimation(CAnimation* ani);
	virtual Transformation* GetTransform() { return this->transform; }
	void Add(string spriteId, DWORD time = 0);
	void Render(float x, float y, float alpha = 1.0f);
};

typedef CAnimation* LPANIMATION;