#pragma once
#include "MasterMario.h"
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24

#define MARIO_BIG_CROUCH_BBOX_HEIGHT 18

class BigMario : public CMasterMario
{
public:

	BigMario();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);


	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);

	virtual RectBox GetBoundingBox();
};