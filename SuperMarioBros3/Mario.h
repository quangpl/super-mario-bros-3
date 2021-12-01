#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.27f
#define MARIO_RUNNING_SPEED		0.48f

#define MARIO_DECREASE_SPEED	 0.0016366f
#define MARIO_ACCEL_WALK_X	0.000376f
#define MARIO_ACCEL_RUN_X	0.0003613f


#define MARIO_JUMP_SPEED_Y		0.8f
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


#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)


enum MarioLevel {
	SMALL = 0,
	BIG = 1,
	FIRE = 2,
	RACCOON = 3,
};

#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	static CMario* __instance;
	CMario* playerState;
	
	
public:
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int untouchable;
	ULONGLONG untouchable_start;
	ULONGLONG transformation_start;
	BOOLEAN isOnPlatform;
	int coin;

	LPGAMEOBJECT holder = NULL;
	bool holding;
	CMario() : CGameObject()
	{
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	void SetPlayerState(CMario* pState) {
		this->playerState = pState;
	}

	CMario* GetPlayerState() {
		return this->playerState;
	}


	int IsCollidable()
	{
		return this->playerState->IsCollidable();
	}

	int IsBlocking() { 
		return this->playerState->IsBlocking();
	}

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CMario* GetInstance();

	void SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
	LPGAMEOBJECT GetHolder() { return this->holder; }

	void SetHolding(bool _holding) { this->holding = _holding; }
	bool GetHolding() { return this->holding; }

	int GetWidth() { return MARIO_BIG_BBOX_WIDTH; }

	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);
	virtual RectBox GetBoundingBox();
};