#include "Mushroom.h"

CMushroom::CMushroom(int level) :CGameObject(x, y)
{
	this->type = Type::MUSHROOM;
	this->vy = 0;
	this->vx = 0;
	this->gravity = 0;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
bool CMushroom::CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy)
{
	if (dynamic_cast<CGoomba*>(gameObject)) {
		return true;
	}
	else {
		return false;
	}
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == UP_MUSHROOM_STATE_UP && abs(start_y - y) >= BRICK_BBOX_HEIGHT) {
		SetState(UP_MUSHROOM_STATE_RUN);
	}
	if (state == UP_MUSHROOM_STATE_UP && abs(start_y - y) >= UP_MUSHROOM_EATABLE_DISTANCE) {
		eatable = true;
	}
	vy += (this->gravity * dt);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	//CAnimations::GetInstance()->Get(UP_MUSHROOM_ANI)->Render(x, y);
	//RenderBoundingBox();
 
}

void CMushroom::SetState(int state)
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
		if (CMario::GetInstance()->GetPositionX() > x) {
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
		isDeleted = true;
		break;
	default:
		break;
	}
}

