#include "Koopas.h"

CKoopas::CKoopas() :CGameObject()
{
	type = Type::KOOPAS;
	koopas_type = KoopaType::RedTroopa;
	SetState(KOOPAS_STATE_WALKING);
	this->gravity = KOOPAS_GRAVITY;
}

//void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	/*left = x - KOOPAS_BBOX_WIDTH/2;
//	top = y - KOOPAS_BBOX_HEIGHT/2;
//	right = left + KOOPAS_BBOX_WIDTH;
//	bottom = top + KOOPAS_BBOX_HEIGHT;
//	switch (state)
//	{
//	case KOOPAS_STATE_IDLE:
//	case KOOPAS_STATE_DIE_MOVE:
//	case KOOPAS_STATE_DIE_BY_ATTACK:
//		left = x - KOOPAS_BBOX_WIDTH / 2;
//		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
//		right = left + KOOPAS_BBOX_WIDTH;
//		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
//		break;
//	default:
//		break;
//	}*/
//}
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
	//DebugOut(L"Vx: %f", vx);
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
		/*	x = this->owner->GetPositionX() + mario->GetNx() * mario->GetWidth();
			y = this->owner->GetPositionY();*/
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
	ani = "ani-red-koopa-troopa-move";

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
		//y = y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		this->vx = 0;
		break;
	case KOOPAS_STATE_DIE_MOVE:
		//y = y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		nx = CMario::GetInstance()->GetNx();
		this->SetVelocityX(nx * KOOPAS_SHELL_RUN_SPEED);
		break;
	default:
		break;
	}
}
