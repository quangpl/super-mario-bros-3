#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "debug.h"
#include "RedMushRoom.h"
#include "ObjectType.h"
#include "CoinEffect.h"
#include "ObjectTypeData.h"
#include "EffectManager.h"
#include "BrickEffect.h"

#define COIN_STATE_NORMAL_COIN 0
#define COIN_STATE_BRICK 1

#define COIN_BBOX_WIDTH 48
#define COIN_BBOX_HEIGHT 48


class CCoin : public CGameObject
{
public:
	void OnNoCollision(DWORD dt);
	CCoin();
	~CCoin();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
	static CCoin* Create(Vec2 fixedPos, int state);
};