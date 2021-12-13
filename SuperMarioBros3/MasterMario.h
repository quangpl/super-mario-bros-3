#pragma once

#include "GameObject.h"
#define MARIO_WALKING_SPEED		0.27f
#define MARIO_RUNNING_SPEED		0.48f

#define MARIO_DECREASE_SPEED	 0.0016366f
#define MARIO_ACCEL_WALK_X	0.000376f
#define MARIO_ACCEL_RUN_X	0.0003613f


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
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_RELEASE_RUNNING	501
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_HOLDING	700
#define MARIO_STATE_RELEASE_HOLDING	701
#define MARIO_STATE_TRANSFORM_SMALL_TO_BIG	800
#define MARIO_STATE_ATTACK	900
#define MARIO_STATE_RELEASE_ATTACK	901



#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

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

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);
	virtual RectBox GetBoundingBox();
};