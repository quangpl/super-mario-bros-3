#pragma once
#include "Goomba.h"
#include "Brick.h"
#include "MushRoom.h"
#include "MasterMario.h"
#include "Koopas.h"

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

class SmallMario : public CMasterMario
{
public:

	SmallMario() : CMasterMario()
	{
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = true;
		coin = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);

	virtual RectBox GetBoundingBox();
};