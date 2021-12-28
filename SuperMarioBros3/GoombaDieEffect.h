#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>
#include "SmallMario.h"

#define GOOMBA_DIE_EFFECT_RUNNING 1
#define STOP_TIMEOUT 500

#define GOOMBA_DIE_EFFECT_WIDTH			45
#define GOOMBA_DIE_EFFECT_HEIGHT	27


class CGoombaDieEffect : public CEffect {
	function<void()> callback;
public:
	int nx = 1;
	int state = -1;
	DWORD startTime;
	CGoombaDieEffect(Vec2 pos, int nx);
	virtual void Update(DWORD dt);
	virtual void Render();
	void Start(function<void()> _callback = 0);
};
