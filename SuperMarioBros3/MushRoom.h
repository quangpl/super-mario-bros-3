#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"
#include "debug.h"
#define MUSHROOM_GRAVITY			0.0003f
#define MUSHROOM_SPEED_Y	0.05f
#define MUSHROOM_SPEED_X	0.05f

#define MUSHROOM_TIME_WAIT_TO_RUN 2000

#define UP_MUSHROOM_ANI	301
#define SUPER_MUSHROOM_ANI	306

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define UP_MUSHROOM_STATE_IDLE 10
#define UP_MUSHROOM_STATE_UP 20
#define UP_MUSHROOM_STATE_RUN 30
#define UP_MUSHROOM_STATE_DIE 40

#define UP_MUSHROOM_EATABLE_DISTANCE 10
class CMushroom : public CGameObject
{
	float start_y;
	bool eatable = false;
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(int goombaType);
	virtual void SetState(int state);
	bool GetEatable() { return this->eatable; }
	void SetEatable(bool _eatable) {  this->eatable = _eatable; }

	void SetStartY(float _start_y) { this->start_y = _start_y; }
};