#pragma once
#include "GameObject.h"
#include "EffectManager.h"
#include "BrickEffect.h"
#include "Stopwatch.h"
#include "BrokenBrickEffect.h"

#define COIN_STATE_NORMAL_COIN 0
#define COIN_STATE_BRICK 1

#define COIN_BBOX_WIDTH 48.0f
#define COIN_BBOX_HEIGHT 48.0f

#define REVERT_TIMEOUT 8000

class CCoin : public CGameObject
{

public:
	int backupState = 0;
	Stopwatch* switchStopWatch;
	bool isSwitching = false;
	Vec2 backupPos;
	void OnNoCollision(DWORD dt);
	CCoin();
	~CCoin();
	void Switch();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual int IsCollidable();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
	static CCoin* Create(Vec2 fixedPos, int state);
};