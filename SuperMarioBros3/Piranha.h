#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Animations.h"
#include "Timer.h"
#include "Stopwatch.h"

#define PIRANHA_STATE_HIDE 0
#define PIRANHA_STATE_DISPLAY 1

#define VENUS_WAIT_TIME 1700
#define VENUS_SPEED 0.13f
#define VENUS_HIDE_DISTANCE 96

#define PIRANHA_SIZE_X 48
#define PIRANHA_SIZE_Y 69

class Piranha : public CGameObject
{
	Stopwatch* stopwatch;
	int movingStep = 0;
	Vec2 ownerPos;
	bool collidable = false;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual void OnNoCollision(DWORD dt);
	virtual RectBox GetBoundingBox();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void TrackPlayerPosition();
public:
	Piranha(Vec2 pos);
	virtual void SetState(int state);
};