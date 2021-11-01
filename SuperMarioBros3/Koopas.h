#pragma once
#include "GameObject.h"
#include "ActivationPoint.h"
#include "Constants.h"
#define KOOPAS_WALKING_SPEED	0.03f
#define KOOPAS_GRAVITY	0.0018f
#define RED_KOOPAS_SPEED_Y		0.06f
#define KOOPAS_DIE_MOVE_SPEED	0.2f
#define KOOPAS_SHELL_RUN_SPEED 0.25
#define KOOPAS_LIMIT_Y		100.0f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING		100
#define KOOPAS_STATE_IDLE			200
#define KOOPAS_STATE_DIE_MOVE		300
#define KOOPAS_STATE_WALKING_DOWN	400
#define KOOPAS_STATE_DIE_BY_ATTACK	999

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


#define KOOPAS_TIME_IDLE			8000
#define KOOPAS_TIME_REVIVAL			1000

enum KoopaType
{
	GreenTroopa = 1,
	RedTroopa = 2,
	GreenParaTroopa = 3,
	RedParaTroopa = 4,
};

class CKoopas : public CGameObject
{
	int koopas_type;
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithActivationPoint(LPCOLLISIONEVENT e);
public:
	CKoopas(int koopas_type, float x, float y);
	virtual void SetState(int state);

};