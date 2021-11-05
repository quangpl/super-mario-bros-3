#include "Brick.h"

CBrick::CBrick(float x, float y, int _brickType, int _child_item_id)
{
	this->brickType = _brickType;
	this->type = Type::BRICK;
	this->vx = 0;
	this->vy = 0;
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
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();

}

void CBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
	//DebugOut(L"start_y: %f, y:%f \n", start_y, y);
	switch (state)
	{
	case BRICK_STATE_MOVE_UP:
		if (abs(y - start_y) >= BRICK_RETURN_DISTANCE) {
			SetState(BRICK_STATE_MOVE_DOWN);
		}
		break;
	case BRICK_STATE_MOVE_DOWN:
		if (y >= start_y) {
			y = start_y;
			vy = 0;
		}
		break;
	default:
		break;
	}
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_MOVE_UP:
		start_y = y;
		if (dynamic_cast<CMushroom*>(this->child_item)) {
			CMushroom* mushroom = dynamic_cast<CMushroom*>(this->child_item);
			mushroom->SetState(UP_MUSHROOM_STATE_UP);
		}
		else if(dynamic_cast<CCoin*>(this->child_item)) {
			CCoin* coin = dynamic_cast<CCoin*>(this->child_item);
			coin->SetState(COIN_STATE_MOVE_UP);
		}
		this->vy = -BRICK_SPEED;
		break;
	case BRICK_STATE_MOVE_DOWN:
		vy = BRICK_SPEED;
		break;
	case BRICK_STATE_BROKEN:
		vy = 0;
		vx = 0;
		break;
	default:
		break;
	}
}


void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}