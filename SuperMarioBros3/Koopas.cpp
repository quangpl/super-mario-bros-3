#include "Koopas.h"

CKoopas::CKoopas() :CGameObject()
{
	type = Type::KOOPAS;
	koopas_type = KoopaType::RedTroopa;
	SetState(KOOPAS_STATE_WALKING);
	this->gravity = KOOPAS_GRAVITY;
}

RectBox CKoopas::GetBoundingBox() {
	bounding_box.left = position.x - size.x / 2;
	bounding_box.top = position.y - size.y / 2;
	bounding_box.right = bounding_box.left + size.x;
	bounding_box.bottom = bounding_box.top + size.y;
	return this->bounding_box;
}
void CKoopas::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

CKoopas* CKoopas::Create(Vec2 pos) {
	CKoopas* koopas = new CKoopas();
	RectBox bounding_box = koopas->GetBoundingBox();
	koopas->SetPosition(Vec2(pos.x, pos.y - (bounding_box.bottom - bounding_box.top) / 2));
	return koopas;
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		nx = -nx;
		vx = nx * abs(vx);
	}

	if (dynamic_cast<CBrick*>(e->obj)) {
		OnCollisionWithBrick(e);
	}
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	e->obj->SetState(BRICK_STATE_BROKEN);
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Switch case for each owner type
	if (this->owner != NULL && dynamic_cast<CMario*>(this->owner)) {
		CMario* mario = dynamic_cast<CMario*>(this->owner);
		int marioDirection = mario->GetSpeed().x > 0 ? 1 : -1;
		position.x = this->owner->GetPosition().x + marioDirection * (mario->GetBoundingBox().right - mario->GetBoundingBox().left);
		position.y = this->owner->GetPosition().y;
	}
	else {
		vy += (KOOPAS_GRAVITY * dt);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	//DebugOut(L"vx: %f", vx);
}


void CKoopas::Render()
{
	switch (state)
	{
	case KOOPAS_STATE_DIE_BY_ATTACK:
		ani = "ani-red-koopa-troopa-shell-idle";
		break;
	case KOOPAS_STATE_DIE_MOVE:
		ani = "ani-red-koopa-troopa-shell-run";
		break;
	case KOOPAS_STATE_IDLE:
		ani = "ani-red-koopa-troopa-shell-idle";
		break;
	case KOOPAS_STATE_WALKING:
	case KOOPAS_STATE_WALKING_DOWN:
		ani = "ani-red-koopa-troopa-move";
		break;
	default:
		break;
	}

	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2(-nx, 1);
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		this->vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_DIE_BY_ATTACK:
		position.y = position.y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		this->vx = 0;
		break;
	case KOOPAS_STATE_DIE_MOVE:
		position.y = position.y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		nx = CMario::GetInstance()->GetNx();
		this->SetVelocityX(nx * KOOPAS_SHELL_RUN_SPEED);
		break;
	default:
		break;
	}
}
