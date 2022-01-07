#include "RedMushroom.h"

CRedMushroom::CRedMushroom() :CGameObject()
{
	this->start_y = 0;
	this->vy = 0;
	this->vx = 0;
	this->gravity = 0;
	// render before Brick
	this->zIndex = 0;
}

RectBox CRedMushroom::GetBoundingBox()
{
	this->bounding_box.left = position.x - MUSHROOM_BBOX_WIDTH / 2;
	this->bounding_box.top = position.y - MUSHROOM_BBOX_HEIGHT / 2;
	this->bounding_box.right = this->bounding_box.left + MUSHROOM_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + MUSHROOM_BBOX_HEIGHT;
	return this->bounding_box;
}

void CRedMushroom::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};
bool CRedMushroom::CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy)
{
	if (dynamic_cast<CGoomba*>(gameObject)) {
		return true;
	}
	else {
		return false;
	}
};

void CRedMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->CanThrough(this, e->nx, e->ny)) return;
	if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CRedMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == UP_MUSHROOM_STATE_UP && abs(start_y - position.y) >= BRICK_BBOX_HEIGHT) {
		SetState(UP_MUSHROOM_STATE_RUN);
	}
	if (state == UP_MUSHROOM_STATE_UP && abs(start_y - position.y) >= UP_MUSHROOM_EATABLE_DISTANCE) {
		eatable = true;
	}
	vy += (this->gravity * dt);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedMushroom::Render()
{
	CAnimations::GetInstance()->Get("ani-super-mushroom")->Render(position.x, position.y);
	RenderBoundingBox();

}

void CRedMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case UP_MUSHROOM_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case UP_MUSHROOM_STATE_UP:
		vx = 0;
		vy = -MUSHROOM_SPEED_Y;
		break;
	case UP_MUSHROOM_STATE_RUN:
		if (CMario::GetInstance()->GetPosition().x > this->position.x) {
			nx = -1;
		}
		else {
			nx = 1;
		}
		vx = nx * MUSHROOM_SPEED_X;
		this->gravity = MUSHROOM_GRAVITY;
		break;
	case UP_MUSHROOM_STATE_DIE:
		vx = 0;
		vy = 0;
		isActive = false;
		this->isDeleted = true;
		break;
	default:
		break;
	}
}

