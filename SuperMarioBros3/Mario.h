#pragma once
#include "GameObject.h"

class CMasterMario;

class CMario : public CGameObject
{
	static CMario* __instance;
	
	
public:
	CMasterMario* playerState;
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

	void SetPlayerState(CMasterMario* pState);

	CMasterMario* GetPlayerState();

	int IsCollidable();

	int IsBlocking();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable();

	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CMario* GetInstance();

	void SetHolder(LPGAMEOBJECT _holder);
	LPGAMEOBJECT GetHolder();

	void SetHolding(bool _holding);
	bool GetHolding();

	virtual void OnKeyUp(int keyCode);

	virtual void OnKeyDown(int keyCode);
	virtual RectBox GetBoundingBox();
};