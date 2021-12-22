#pragma once
#include "Utils.h"
#include "Transformation.h"

class PowerMeter
{
	Transformation trans;
public:
	int level;
	Vec2 position;
	Vec2 size;
	DWORD dt;
	PowerMeter();
	void Render();
	void Update(DWORD dt);
};

