#pragma once
#include "MasterMario.h"
#include "Tail.h"
#include "Stopwatch.h"
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24

#define MARIO_BIG_CROUCH_BBOX_HEIGHT 18
#define TAIL_TIMEOUT 500
#define PMETER_UP_STEP 0.008f
#define	PMETER_MAX  7
#define PMETER_DOWN_STEP 0.0016f
#define MARIO_FLOATING_SPEED 0.021f

class RaccoonMario : public CMasterMario
{
public:
	CTail* tail;
	Stopwatch* stopwatch;
	Stopwatch* flyStopwatch;
	RaccoonMario();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void PowerCalculator(DWORD dt);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void KeyboardHandler();

	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);

	virtual RectBox GetBoundingBox();
};