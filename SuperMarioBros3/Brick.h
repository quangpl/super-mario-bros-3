#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "debug.h"
#include "MushRoom.h"

#define BRICK_ANI_NORMAL		702
#define BRICK_ANI_BROKEN		703

#define BRICK_STATE_NORMAL		1
#define BRICK_STATE_BROKEN		2

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
	Empty = 0
};
class CBrick : public CGameObject
{
	int start_shipping;
	float start_y;
public:
	int brickType;
	int child_item_id = BrickChildItem::Empty;
	LPGAMEOBJECT child_item = NULL;

public:
	CBrick(float x, float y, int brickType, int child_item_id);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);

	int GetChildItemId() { return this->child_item_id; }
	void SetChildItemId(int _child_item_id) { this->child_item_id = _child_item_id; }

	LPGAMEOBJECT GetChildItem() { return this->child_item; }
	void SetChildItem(LPGAMEOBJECT _child_item) { this->child_item = _child_item; }

};