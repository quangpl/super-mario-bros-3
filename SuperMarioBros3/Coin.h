#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_ANI_IDLE 351
#define COIN_ANI_ROTATION 352

#define COIN_STATE_MOVE_UP 1
#define COIN_STATE_MOVE_DOWN 2

#define COIN_RETURN_DISTANCE 40
#define COIN_HIDE_DISTANCE 10
#define COIN_SPEED 0.2f

class CCoin : public CGameObject {
	float start_y;
public:
	void Render();
	void Update(DWORD dt) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy){return true;}
	int IsBlocking() { return 0; }
	void SetState(int state);
};