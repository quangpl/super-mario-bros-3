#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Animations.h"
#include "Timer.h"
#include "Stopwatch.h"
#include "Fireball.h"
#define VENUS_STATE_HIDE 0
#define VENUS_STATE_DISPLAY 1

#define VENUS_SIZE_X 48
#define VENUS_SIZE_Y 96

#define VENUS_WAIT_TIME 1700
#define VENUS_SPEED  0.13f
#define VENUS_HIDE_DISTANCE 96
#define VENUS_N_POOLED_BULLETS  1
#define VENUS_BULLET_SPEED  0.18f
#define VENUS_SHOOT_WAIT_TIME  VENUS_WAIT_TIME / 2

enum VenusType {
	RedVenus,
	GreenVenus
};

class Venus : public CGameObject
{
	int movingStep = 0;
	Vec2 ownerPos;
	bool collidable = false;
	int direction = 1;
	int type = VenusType::GreenVenus;
	int targetLocking = 1;
	Stopwatch* shootStopwatch;
	Stopwatch* movingStopwatch;
	vector<Fireball*> fireballs;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable();
	virtual void OnNoCollision(DWORD dt);
	virtual RectBox GetBoundingBox();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void RefindMario();
	void OnGoingToCamera();

public:
	Venus(Vec2 pos, int type);
	virtual void SetState(int state);
};