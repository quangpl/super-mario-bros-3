#pragma once
#include "Utils.h"
#include "PowerMeter.h"
class Hud
{
	PowerMeter* powerMeter = NULL;
public:
	void LoadFromTmx(string tmxPath);
	Hud(string tmxPath, Vec2 pos, Vec2 size);

	virtual void Update(DWORD dt);

	virtual void Render();

};

