#include "Brick.h"

CBrick::CBrick(float x, float y, int brickType, int _child_item_id)
{
	this->brickType = brickType;
	this->type = Type::BRICK;
	this->x = x;
	this->y = y;
	this->child_item_id = _child_item_id;
	if (brickType == BrickType::Question) {
		state = BRICK_STATE_NORMAL;
	}
	else {
		state = BRICK_ANI_BROKEN;
	}
}

CBrick::~CBrick()
{

}

void CBrick::Render()
{
	int ani;
	if (this->state == BRICK_STATE_NORMAL) {
		ani = BRICK_ANI_NORMAL;
	}
	else {
		ani = BRICK_ANI_BROKEN;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x,y);
	//RenderBoundingBox();

}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	//if (state == BRICK_STATE_BROKEN && GetTickCount64() - start_shipping > BRICK_REVERT_POSITION_TIME) {
	//	y = y + BRICK_SHIP_DISTANCE;
	//}
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_BROKEN:
		start_shipping = GetTickCount64();
		if (dynamic_cast<CMushroom*>(this->child_item)) {
			CMushroom* mushroom = dynamic_cast<CMushroom*>(this->child_item);
			mushroom->SetState(UP_MUSHROOM_STATE_UP);
		}
		break;
	default:
		break;
	}
}


void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}