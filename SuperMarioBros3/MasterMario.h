#pragma once

#include "GameObject.h"
#include "Koopas.h"
#define MARIO_WALKING_SPEED		0.27f
#define MARIO_RUNNING_SPEED		0.48f

#define MARIO_DECREASE_SPEED	 0.0016366f
#define MARIO_ACCEL_WALK_X	0.000376f
#define MARIO_ACCEL_RUN_X	0.0003613f
#define MARIO_SKID_ACCELERATION  0.001104f;

#define MARIO_JUMP_SPEED_Y		0.9f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_RUNNING	400
#define MARIO_STATE_RELEASE_RUNNING	501
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_HOLDING	700
#define MARIO_STATE_RELEASE_HOLDING	701
#define MARIO_STATE_TRANSFORM_SMALL_TO_BIG	800
#define MARIO_STATE_ATTACK	900
#define MARIO_STATE_RELEASE_ATTACK	901
#define MARIO_STATE_FLY	1000
#define MARIO_STATE_FLOAT	1001


#define MARIO_STATE_WARP_NONE 1100
#define MARIO_STATE_WARP_VERTICAL 1101
#define MARIO_STATE_WARP_HORIZONTAL 1102

#define MARIO_STATE_SKID	1200

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_MIN_HIGH_JUMP_HEIGHT 97

#define MARIO_RUN_DRAG 0.0016366f
#define PMETER_DOWN_STEP 0.0016f
#define PMETER_UP_STEP 0.008f
#define	PMETER_MAX  7 // TODO: it will be best if solve deviation issue

class CMario;

#define MARIO_UNTOUCHABLE_TIME 2500
class CMasterMario
{

public:
	string ani;
	CMario* mario;
	CMasterMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void KeyboardHandler();
	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);
	virtual void OnDamaged();
	virtual void OnHitEnermy(CGameObject* obj);
	void PowerCalculator(DWORD dt);
	void OnReleaseHolding();
	void OnKickShell(CGameObject *koopas);
	virtual RectBox GetBoundingBox();
};