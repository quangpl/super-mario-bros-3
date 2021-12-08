#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>
#include "SmallMario.h"

#define MARIO_GROW_UP_EFFECT_RUNNING 1
#define STOP_TIMEOUT 1000
class CMarioGrowEffect : public CEffect {
	function<void()> callback;
public:
	int nx = 1;
	int state = -1;
	DWORD startTime;
	CMarioGrowEffect(Vec2 pos, int nx);
	virtual void Update(DWORD dt);
	virtual void Render();
	void Start(function<void()> _callback = 0);
};

