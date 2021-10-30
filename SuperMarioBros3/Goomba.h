#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"
#include "Timer.h"
#define GOOMBA_GRAVITY 0.0018f

#define GOOMBA_BBOX_WIDTH			16
#define GOOMBA_BBOX_HEIGHT			15
#define GOOMBA_BBOX_HEIGHT_DIE		9

#define RED_PARA_BBOX_WIDTH			20
#define RED_PARA_BBOX_HEIGHT		24

#define GOOMBA_DIE_TIMEOUT 500 

#define GOOMBA_WALKING_SPEED		0.03f;
#define GOOMBA_JUMP_LOW_SPEED		0.18f;


#define GOOMBA_STATE_DIE	10
#define GOOMBA_STATE_WALKING	20
#define GOOMBA_STATE_JUMP_LOW	30
#define GOOMBA_STATE_JUMP_HIGH	40


#define GOOMBA_ANI_WALKING 601
#define GOOMBA_ANI_DIE 602
#define GOOMBA_ANI_DIE_BY_ATTACK 603

#define GOOMBA_WING_RED_ANI_WALKING 611
#define GOOMBA_WING_RED_ANI_JUMP_LOW 612
#define GOOMBA_WING_RED_ANI_JUMP_HIGH 613

#define GOOMBA_RED_ANI_WALKING 614
#define GOOMBA_RED_ANI_DIE_BY_CRUSH 615
#define GOOMBA_RED_ANI_DIE_BY_ATTACK 616

#define TIME_GOOMBA_WAIT_TO_JUMP_LOW 500
#define TIME_GOOMBA_WAIT_TO_JUMP_HIGH 500


enum GoombaLevel
{
	Nomal = 1,
	Red = 2,
	RedWing = 3
};



class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;
	ULONGLONG die_start;
	ULONGLONG waiting_time;
	int jump_step = 0;
	bool is_on_ground;
	CTimer* timer;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba(int goombaType);
	virtual void SetState(int state);
	int GetLevel() { return this->level; }
	void SetLevel(int _level) { level = _level; }

};