#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"
#include "Goomba.h"
#include "Timer.h"
#include "Tail.h"
#include "Koopas.h"
#include "Stopwatch.h"

#define REDWING_GOOMBA_JUMP_HIGH_SPEED	0.5

enum RedWingGoombaLevel {
	RedWing = 1,
	Red = 2
};


class CRedWingGoomba : public CGameObject
{
protected:
	ULONGLONG die_start;
	int level;
	ULONGLONG waiting_time;
	int jump_step = 0;
	bool is_on_ground;
	CTimer* timer;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual void OnNoCollision(DWORD dt);
	virtual RectBox GetBoundingBox();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);

public:
	CRedWingGoomba();
	static CRedWingGoomba* Create(Vec2 position);
	virtual void SetState(int state);
	int GetLevel() { return this->level; }
	void SetLevel(int _level) { level = _level; }
};