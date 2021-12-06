#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"
#include "Goomba.h"
#include "Timer.h"
#include "Koopas.h"
#include "Stopwatch.h"

#define GOOMBA_GRAVITY 0.0018f
#define GOOMBA_HIT_SPEED 0.3f
#define GOOMBA_BBOX_WIDTH			45
#define GOOMBA_BBOX_HEIGHT			45
#define GOOMBA_BBOX_HEIGHT_DIE	27

#define RED_PARA_BBOX_WIDTH			20
#define RED_PARA_BBOX_HEIGHT		24

#define GOOMBA_DIE_TIMEOUT 500 

#define GOOMBA_WALKING_SPEED		0.05f;
#define GOOMBA_JUMP_LOW_SPEED		0.2f;
#define GOOMBA_JUMP_HIGH_SPEED		0.4f;



#define GOOMBA_STATE_DIE	10
#define GOOMBA_STATE_WALKING	20
#define GOOMBA_STATE_JUMP_LOW	30
#define GOOMBA_STATE_JUMP_HIGH	40
#define GOOMBA_STATE_DIE_BY_ATTACK	59



#define GOOMBA_ANI_WALKING 601
#define GOOMBA_ANI_DIE 602
#define GOOMBA_ANI_DIE_BY_ATTACK 603

#define GOOMBA_WING_RED_ANI_WALKING 611
#define GOOMBA_WING_RED_ANI_JUMP_LOW 612
#define GOOMBA_WING_RED_ANI_JUMP_HIGH 613

#define GOOMBA_RED_ANI_WALKING 614
#define GOOMBA_RED_ANI_DIE_BY_CRUSH 615
#define GOOMBA_RED_ANI_DIE_BY_ATTACK 616

#define TIME_GOOMBA_WAIT_TO_JUMP_LOW 1500
#define TIME_GOOMBA_WAIT_TO_JUMP_HIGH 300




class CRedWingGoomba : public CGameObject
{
protected:
	int level;
	ULONGLONG waiting_time;
	int jump_step = 0;
	bool is_on_ground;
	CTimer* timer;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual RectBox GetBoundingBox();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
public:
	CRedWingGoomba();
	static CRedWingGoomba* Create(Vec2 position);
	virtual void SetState(int state);
	int GetLevel() { return this->level; }
	void SetLevel(int _level) { level = _level; }
};