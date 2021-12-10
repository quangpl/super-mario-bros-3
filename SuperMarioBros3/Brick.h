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

#define BRICK_RETURN_DISTANCE 5
#define BRICK_ANI_NORMAL		702
#define BRICK_ANI_BROKEN		703

#define BRICK_SPEED 0.1f

#define BRICK_STATE_NORMAL		1
#define BRICK_STATE_BROKEN		2
#define BRICK_STATE_MOVE_UP		3
#define BRICK_STATE_MOVE_DOWN	4
#define BRICK_STATE_HIT		5

// TODO: need improve with Effect
#define BRICK_SHIP_DISTANCE 4
#define BRICK_REVERT_POSITION_TIME 2000

enum class BrickType {
	QuestionBrick,
	DiamondBrick
};

class CBrick : public CGameObject
{
public:
	Vec2 size;
	BrickType brickType;
	ObjectType reward = ObjectTypeData::QuestionCoin;
	void OnNoCollision(DWORD dt);
	CBrick();
	~CBrick();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
	static CBrick* Create(Vec2 fixedPos, MapData& data);
};