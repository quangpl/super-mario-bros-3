#pragma once
#include "GameObject.h"

#define KOOPAS_WALKING_SPEED	0.03f;
#define KOOPAS_SPEED_Y			0.16f;
#define RED_KOOPAS_SPEED_Y		0.06f;
#define KOOPAS_DIE_MOVE_SPEED	0.2f;

#define KOOPAS_LIMIT_Y		100.0f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING		100
#define KOOPAS_STATE_IDLE			200
#define KOOPAS_STATE_DIE_MOVE		300
#define KOOPAS_STATE_WALKING_DOWN	400
#define KOOPAS_STATE_DESTROY		999

#define KOOPAS_ANI_WALKING_LEFT		501
#define KOOPAS_ANI_WALKING_RIGHT	502
#define KOOPAS_ANI_DIE				503
#define KOOPAS_ANI_DIE_SUPINE		504
#define KOOPAS_ANI_RELIFE			505 
#define KOOPAS_ANI_RELIFE_SUPINE	506
#define KOOPAS_ANI_DIE_MOVE			507
#define KOOPAS_ANI_DIE_MOVE_SUPINE	508

#define PARA_KOOPAS_ANI_LEFT		511
#define PARA_KOOPAS_ANI_RIGHT		512


#define KOOPAS_TIME_IDLE			8000
#define KOOPAS_TIME_RELIFE			1000


class CKoopas : public CGameObject
{
	int koopas_type;
	float start_x;
	float start_y;
public:
	CKoopas(int koopas_type, float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};