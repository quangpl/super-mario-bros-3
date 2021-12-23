#pragma once
#include "Goomba.h"
#include "Brick.h"
#include "RedMushRoom.h"
#include "RedWingGoomba.h"
#include "Koopas.h"
#include "MasterMario.h"

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 15
class CMasterMario;
class SmallMario : public CMasterMario
{
public:

	SmallMario();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	virtual RectBox GetBoundingBox();
};