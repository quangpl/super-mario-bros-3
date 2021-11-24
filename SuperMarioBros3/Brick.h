#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "debug.h"
#include "MushRoom.h"
#include "CoinEffect.h"
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

enum BrickType
{
	Question = 2,
	Bronze = 4,
};
enum BrickChildItem {
	MushRoom = 4,
	Empty = 0,
	Coin = 2
};
class CBrick : public CGameObject
{
public:
	int brickType;
	int child_item_id = BrickChildItem::Empty;
	LPGAMEOBJECT child_item = NULL;
	void OnNoCollision(DWORD dt);
	CBrick(Vec2 position, int brickType, int child_item_id);
	~CBrick();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
	int GetChildItemId() { return this->child_item_id; }
	void SetChildItemId(int _child_item_id) { this->child_item_id = _child_item_id; }
	LPGAMEOBJECT GetChildItem() { return this->child_item; }
	void SetChildItem(LPGAMEOBJECT _child_item) { this->child_item = _child_item; }

	static CBrick* Create(Vec2 pos);
};