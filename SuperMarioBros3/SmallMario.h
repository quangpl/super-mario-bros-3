#pragma once
#include "Goomba.h"
#include "Brick.h"
#include "MushRoom.h"
#include "RedWingGoomba.h"
#include "Koopas.h"

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12
class SmallMario : public CMasterMario
{
public:

	SmallMario() : CMasterMario()
	{
		
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	virtual RectBox GetBoundingBox();
};