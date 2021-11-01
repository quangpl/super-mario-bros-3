#include "Koopas.h"

CKoopas::CKoopas(int _koopas_type, float x, float y) :CGameObject(x, y)
{
	type = Type::KOOPAS;
	koopas_type = _koopas_type;
	SetState(KOOPAS_STATE_WALKING);
	this->gravity = KOOPAS_GRAVITY;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH/2;
	top = y - KOOPAS_BBOX_HEIGHT/2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
	switch (state)
	{
	case KOOPAS_STATE_IDLE:
	case KOOPAS_STATE_DIE_MOVE:
		top = y + KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE;
		break;
	case KOOPAS_STATE_DIE_BY_ATTACK:
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
		break;
	default:
		break;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

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
		vx = -vx;
	}
}

void CKoopas::OnCollisionWithActivationPoint(LPCOLLISIONEVENT e)
{
	CActivationPoint* activation_point = dynamic_cast<CActivationPoint*>(e->obj);
	int command = activation_point->GetCommand();
	if (command == ActivationCommand::TurnKoopasAround) {
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += (KOOPAS_GRAVITY * dt);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	//DebugOut(L"ani:%d \n", ani);
	switch (state)
	{
	case KOOPAS_STATE_DIE_BY_ATTACK:
		ani = PARA_KOOPAS_ANI_DIE;
		break;
	case KOOPAS_STATE_DIE_MOVE:
		ani = KOOPAS_ANI_DIE_MOVE_SUPINE;
		break;
	case KOOPAS_STATE_IDLE:
		ani = KOOPAS_ANI_DIE;
		break;
	case KOOPAS_STATE_WALKING:
	case KOOPAS_STATE_WALKING_DOWN:
		if (koopas_type == KoopaType::RedTroopa)
		{
			if (vx > 0)
				ani = PARA_KOOPAS_ANI_RIGHT;
			else
			{
				ani = PARA_KOOPAS_ANI_LEFT;
			}
		}
		else
		{
			if (vx > 0)
				ani = KOOPAS_ANI_WALKING_RIGHT;
			else
			{
				ani = KOOPAS_ANI_WALKING_LEFT;
			}
		}
		break;
	default:
		break;
	}

	CAnimations::GetInstance()->Get(ani)->Render(x, y);

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
		y = y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		this->vx = 0;
	default:
		break;
	}
}
