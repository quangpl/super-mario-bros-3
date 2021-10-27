#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"

CKoopas::CKoopas(int koopas_type, float x, float y)
{
	type = Type::KOOPAS;
	koopas_type = koopas_type;
	this->start_x = x;
	this->start_y = y;
	this->vx = KOOPAS_WALKING_SPEED;
	this->vy = RED_KOOPAS_SPEED_Y;
}

void CKoopas::Render()
{
	//DebugOut(L"ani:%d \n", ani);
	ani = PARA_KOOPAS_ANI_LEFT;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
}
