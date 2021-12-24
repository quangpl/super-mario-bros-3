#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "Brick.h"
#define PSWITCH_SIZE 45

#define PSWITCH_STATE_NORMAL 1
#define PSWITCH_STATE_PRESSED 2

class PSwitch : public CGameObject
{
public:
	PSwitch(Vec2 pos);
	~PSwitch();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual void OnNoCollision(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable();
	virtual void SetState(int state);
};