#pragma once
#include "GameObject.h"
#include "Constants.h"
#define MUSHROOM_GRAVITY			0.06f
#define MUSHROOM_SPEED_Y	0.05f
#define MUSHROOM_SPEED_X	0.04f


#define UP_MUSHROOM_ANI	301
#define SUPER_MUSHROOM_ANI	306

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define UP_MUSHROOM_STATE_IDLE 10
#define UP_MUSHROOM_STATE_UP 20
#define UP_MUSHROOM_STATE_RUN 30


class CMushroom :
	public CGameObject
{

public:
	CMushroom(int t);
	~CMushroom();

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};