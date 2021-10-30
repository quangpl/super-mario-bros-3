#include "MushRoom.h"

CMushroom::CMushroom(int t) {
	this->type = Type::MUSHROOM;
	vx = MUSHROOM_SPEED_Y;
	vy = MUSHROOM_SPEED_Y;
}
CMushroom::~CMushroom()
{

}

void CMushroom::Render()
{
	CAnimations::GetInstance()->Get(UP_MUSHROOM_ANI)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += (MUSHROOM_GRAVITY * dt);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
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
		vy = -MUSHROOM_SPEED_Y;
		break;
	case UP_MUSHROOM_STATE_RUN:
		vx = nx * MUSHROOM_SPEED_Y;
		vy = MUSHROOM_SPEED_Y;
		break;
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
}