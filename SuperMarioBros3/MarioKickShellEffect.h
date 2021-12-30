#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>
#include "SmallMario.h"

#define MARIO_KICK_SHELL_EFFECT_RUNNING 1

class CMarioKickShellEffect : public CEffect {
	function<void()> callback;
public:
	int nx = 1;
	int state = -1;
	ULONGLONG startTime = 0;
	CMarioKickShellEffect(Vec2 pos, int nx);
	virtual void Update(DWORD dt);
	virtual void Render();
	void Start(function<void()> _callback = 0);
};

