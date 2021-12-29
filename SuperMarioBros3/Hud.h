#pragma once
#include "Utils.h"
#include "PowerMeter.h"
#include "Transformation.h"

class Hud
{
	Transformation trans;
	PowerMeter* powerMeter = NULL;
public:
	Vec2 position;
	void LoadFromTmx(string tmxPath);
	Hud(string tmxPath, Vec2 pos, Vec2 size);

	virtual void Update(DWORD dt);

	virtual void Render();

};

