#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>
#include "Debris.h"


class BrokenBrickEffect : public CEffect {
	function<void()> callback;
	vector<Debris*> debrises;
public:
	int nx = 1;
	int state = -1;
	DWORD startTime;
	BrokenBrickEffect(Vec2 pos);
	virtual void Update(DWORD dt);
	virtual void Render();
	void Start(function<void()> _callback = 0);
};

