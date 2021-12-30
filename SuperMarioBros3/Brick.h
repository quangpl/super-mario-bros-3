#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "debug.h"
#include "RedMushRoom.h"
#include "ObjectType.h"
#include "CoinEffect.h"
#include "ObjectTypeData.h"
#include "EffectManager.h"
#include "PSwitch.h"
#include "BrickEffect.h"
#include "MarioLeaf.h"

#define BRICK_ANI_NORMAL		702
#define BRICK_ANI_BROKEN		703


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
	Vec2 backupPos;
	Vec2 size;
	BrickType brickType = BrickType::QuestionBrick;
	ObjectType reward = ObjectTypeData::QuestionCoin;
	void OnNoCollision(DWORD dt);
	CBrick();
	~CBrick();
	void GenerateRewardByMarioLevel();
	virtual void Render();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsCollidable();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
	static CBrick* Create(Vec2 fixedPos, MapData& data);
};