#pragma once
#include "GameObject.h"
#include "debug.h"
#include "SceneManager.h"

#define MARIO_TAIL_WIDTH 70.0f
#define MARIO_TAIL_BBOX_SIZE 12
#define MARIO_TAIL_HIT_TIME 500
class CMario;
class Stopwatch;

class CTail : public CGameObject
{
public:
	DWORD dt;
	CMario* owner;
	Stopwatch* stopwatch;
	long hitTime;
	int attackNx;
	void OnNoCollision(DWORD dt);
	CTail(CMario* owner);
	~CTail();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);

	void Attack();

	void AttackHandler();
};