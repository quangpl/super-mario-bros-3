#pragma once
#include "GameObject.h"
#include "Animations.h"

#define FIREBALL_SIZE 24
#define FIREBALL_SPEED 0.09f
#define CELL_SIZE 48
#define POSITION_ADJUSTMENT 15


class Fireball : public CGameObject
{
	DWORD dt;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable();
	virtual void OnNoCollision(DWORD dt);
	virtual RectBox GetBoundingBox();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Fireball();
	virtual void SetState(int state);
	void Shoot(RectBox box, int nx);
	Vec2 GetUnitVector(Vec2 source);
	

};