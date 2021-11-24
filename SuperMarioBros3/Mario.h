#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Animation.h"
#include "Animations.h"
#include "MushRoom.h"
#include "Koopas.h"
#include "debug.h"

#define MARIO_TRANSFORMATION_TIME 20000
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_DECREASE_SPEED	 0.0065f
#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0001f

#define MARIO_ACCEL_INCREMENT 0.00001f

#define MARIO_JUMP_SPEED_Y		0.52f
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




#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 0
#define ID_ANI_MARIO_IDLE_LEFT 20

#define ID_ANI_MARIO_WALKING_RIGHT 1
#define ID_ANI_MARIO_WALKING_LEFT 21

#define ID_ANI_MARIO_RUNNING_RIGHT 5
#define ID_ANI_MARIO_RUNNING_LEFT 25

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 2
#define ID_ANI_MARIO_JUMP_WALK_LEFT 22

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 2
#define ID_ANI_MARIO_JUMP_RUN_LEFT 22

#define ID_ANI_MARIO_SIT_RIGHT 4
#define ID_ANI_MARIO_SIT_LEFT 24

#define ID_ANI_MARIO_BRACE_LEFT 6
#define ID_ANI_MARIO_BRACE_RIGHT 26

#define ID_ANI_MARIO_IDLE_HOLD_SHELL_RIGHT 7
#define ID_ANI_MARIO_WALK_HOLD_SHELL_RIGHT 8
#define ID_ANI_MARIO_JUMP_HOLD_SHELL_RIGHT 9

#define ID_ANI_MARIO_IDLE_HOLD_SHELL_LEFT 27
#define ID_ANI_MARIO_WALK_HOLD_SHELL_LEFT 28
#define ID_ANI_MARIO_JUMP_HOLD_SHELL_LEFT 29

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 40
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 60

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 41
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 61

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 43
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 63

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 44
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 64

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 42
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 62

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 42
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 62

#define ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_RIGHT 45
#define ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_RIGHT 46
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_RIGHT 47

#define ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_LEFT 65
#define ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_LEFT 66
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_LEFT 67

#define ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_LEFT 70
#define ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_RIGHT 71

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	static CMario* __instance;

	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	ULONGLONG transformation_start;
	BOOLEAN isOnPlatform;
	int coin;
	int backup_state;

	RectBox move_limitation = RectBox(9999, 9999, 9999, 9999);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();


	LPGAMEOBJECT holder = NULL;
	bool holding;
public:

	CMario() : CGameObject()
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CMario* GetInstance();

	void SetLevel(int _level);
	int GetLevel() { return this->level; }

	void SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
	LPGAMEOBJECT GetHolder() { return this->holder; }

	void SetHolding(bool _holding) { this->holding = _holding; }
	bool GetHolding() { return this->holding; }

	int GetWidth() { return MARIO_BIG_BBOX_WIDTH; }

	void OnKeyUp(int keyCode);

	void OnKeyDown(int keyCode);

	void SetMoveLimitation(RectBox limitation) {
		this->move_limitation = limitation;
	}

	virtual RectBox GetBoundingBox();
};