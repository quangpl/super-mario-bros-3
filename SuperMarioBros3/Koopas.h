#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mario.h"
#include "Transformation.h"
#include "Stopwatch.h"
#include "Brick.h"
#include "Tail.h"

#define KOOPAS_HIT_VX 0.15f
#define KOOPAS_HIT_VY 0.5f

#define KOOPAS_WALKING_SPEED	0.03f
#define KOOPAS_GRAVITY	0.0018f
#define RED_KOOPAS_SPEED_Y		0.06f
#define KOOPAS_SHELL_RUN_SPEED 0.4f

#define KOOPAS_CROUCH_TO_REPAWN_TIME 7000
#define KOOPAS_RESPAWN_TO_REVIVAL_TIME 4000


#define KOOPAS_BBOX_WIDTH 16*
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING		100
#define KOOPAS_STATE_IDLE			200
#define KOOPAS_STATE_DIE_MOVE		300
#define KOOPAS_STATE_WALKING_DOWN	400
#define KOOPAS_STATE_DIE_BY_ATTACK	999
// hit : hat tung
#define KOOPAS_STATE_DIE_BY_HIT		1000
#define KOOPAS_STATE_RESPAWN		500

#define KOOPAS_STATE_DIE		1100

// Green
#define KOOPAS_ANI_WALKING_LEFT		501
#define KOOPAS_ANI_WALKING_RIGHT	502

#define KOOPAS_ANI_DIE				503
#define KOOPAS_ANI_DIE_SUPINE		504

#define KOOPAS_ANI_REVIVAL			505 
#define KOOPAS_ANI_REVIVAL_SUPINE	506

#define KOOPAS_ANI_DIE_MOVE			507
#define KOOPAS_ANI_DIE_MOVE_SUPINE	508




//Red
#define PARA_KOOPAS_ANI_LEFT		511
#define PARA_KOOPAS_ANI_RIGHT		512
#define PARA_KOOPAS_ANI_DIE			513
#define PARA_KOOPAS_ANI_DIE_SUPINE	514
#define PARA_KOOPAS_ANI_DIE_SPIN	517


enum KoopaType
{
	GreenTroopa = 1,
	RedTroopa = 2,
	GreenParaTroopa = 3,
	RedParaTroopa = 4,
};

class CKoopas : public CGameObject
{
	ULONGLONG die_start = 0;
	int shell_step = 0;
	Vec2 transformation = { 1.0f,1.0f };
	Stopwatch* revivalStopWatch;
	Vec2 size = Vec2(45, 45);
	int koopas_type;
	LPGAMEOBJECT owner = NULL;
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual int IsCollidable();
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);

public:
	virtual RectBox GetBoundingBox();
	CKoopas();
	virtual void SetState(int state);

	void SetOwner(LPGAMEOBJECT _owner) { this->owner = _owner; }
	LPGAMEOBJECT GetOwner() { return this->owner; }

	static CKoopas* Create(Vec2 position);

};