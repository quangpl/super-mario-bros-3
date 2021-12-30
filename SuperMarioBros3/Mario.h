﻿#pragma once
#include "GameObject.h"

enum MarioLevel {
	Small = 0,
	Big,
	Raccoon
};

class CMasterMario;

class CMario : public CGameObject
{
	static CMario* __instance;


public:
	int level;
	float power;
	RectBox moveLimitaion;
	CMasterMario* playerState;
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;
	bool isJumping;
	bool isAttacking;
	LPGAMEOBJECT holder;
	bool holding;
	CMario() : CGameObject()
	{
		this->power = 0;
		this->level = MarioLevel::Small;
		this->playerState = NULL;
		this->maxVx = 0.0f;
		this->ax = 0.0f;
		this->ay = 0.002f;
		this->untouchable = 0;
		this->untouchable_start = -1;
		this->isOnPlatform = true;
		this->coin = 0;
		holding = false;
		isJumping = false;
		isAttacking = false;
		this->holder = NULL;
		this->isSitting = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	void SetPlayerState(CMasterMario* pState);

	CMasterMario* GetPlayerState();

	int IsCollidable();

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnBlockingOnY(int jetY);
	virtual void OnBlockingOnX(int jetX);

	void StartUntouchable();

	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CMario* GetInstance();

	void SetHolder(LPGAMEOBJECT _holder);
	LPGAMEOBJECT GetHolder();

	void SetHolding(bool _holding);
	bool GetHolding();

	void SetLevel(int level);
	int GetLevel();

	float GetPower();
	void SetPower(float newPower);

	virtual void OnKeyUp(int keyCode);
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);


	virtual void OnKeyDown(int keyCode);
	virtual RectBox GetBoundingBox();
};