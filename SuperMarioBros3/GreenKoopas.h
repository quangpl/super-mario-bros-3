#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mario.h"
#include "Transformation.h"
#include "Stopwatch.h"
#include "Brick.h"
#include "Tail.h"



#define GREEN_KOOPAS_JUMP_SPEED 0.6f

class GreenKoopas : public CGameObject
{
	bool isOnPlatForm = false;
	bool canJump = false;
	int shell_step = 0;
	Vec2 transformation = { 1.0f,1.0f };
	Stopwatch* revivalStopWatch;
	Vec2 size = Vec2(45, 45);
	int koopas_type;
	LPGAMEOBJECT owner = NULL;
	ULONGLONG die_start = 0;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnBlockingOnY(int jetY);

public:
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual RectBox GetBoundingBox();
	GreenKoopas();
	virtual void SetState(int state);

	virtual int IsCollidable();
	void SetOwner(LPGAMEOBJECT _owner) { this->owner = _owner; }
	LPGAMEOBJECT GetOwner() { return this->owner; }

	static GreenKoopas* Create(Vec2 position, bool canJump);

};