#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"
#include "debug.h"
#include "Goomba.h"

#define MUSHROOM_GRAVITY			0.001f
#define MUSHROOM_SPEED_Y	0.15f
#define MUSHROOM_SPEED_X	0.15f


#define MUSHROOM_TIME_WAIT_TO_RUN 2000


#define MUSHROOM_BBOX_WIDTH 48
#define MUSHROOM_BBOX_HEIGHT 48

#define UP_MUSHROOM_STATE_IDLE 10
#define UP_MUSHROOM_STATE_UP 20
#define UP_MUSHROOM_STATE_RUN 30
#define UP_MUSHROOM_STATE_DIE 40

#define UP_MUSHROOM_EATABLE_DISTANCE 20
class CRedMushroom : public CGameObject
{
	float start_y;
	bool eatable = false;
protected:
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);

public:
	CRedMushroom();
	virtual void SetState(int state);
	bool GetEatable() { return this->eatable; }
	void SetEatable(bool _eatable) {  this->eatable = _eatable; }
	void SetStartY(float _start_y) { this->start_y = _start_y; }
};