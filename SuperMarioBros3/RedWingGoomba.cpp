#include "RedWingGoomba.h"

CRedWingGoomba* CRedWingGoomba::Create(Vec2 position) {
	CRedWingGoomba* goomba = new CRedWingGoomba();
	goomba->SetPosition(Vec2(position.x, position.y - 50));
	return goomba;
}

CRedWingGoomba::CRedWingGoomba() :CGameObject()
{
	this->jump_step = 1;
	this->level = RedWingGoombaLevel::RedWing;
	this->gravity = GOOMBA_GRAVITY;
	if (nx > 0) {
		nx *= -1;
	}
	this->timer = new CTimer(0);
	SetState(GOOMBA_STATE_WALKING);
}

RectBox CRedWingGoomba::GetBoundingBox() {
	int bbox_height = this->state == GOOMBA_STATE_DIE ? GOOMBA_BBOX_HEIGHT_DIE : GOOMBA_BBOX_HEIGHT;
	this->bounding_box.left = position.x - GOOMBA_BBOX_WIDTH / 2;
	this->bounding_box.top = position.y - bbox_height / 2;
	this->bounding_box.right = this->bounding_box.left + GOOMBA_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + bbox_height;
	return this->bounding_box;
}

void CRedWingGoomba::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void CRedWingGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
		is_on_ground = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CTail*>(e->obj))
	{
		this->SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

void CRedWingGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	if (e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) {
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

void CRedWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += (this->gravity * dt);
	if ((state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_DIE_BY_ATTACK) && GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	CMario* mario = CMario::GetInstance();
	if (timer->IsRunning() && !timer->IsTimeUp()) {
		return;
	}
	if (is_on_ground && level == RedWingGoombaLevel::RedWing) {
		switch (jump_step)
		{
		case 1:
			nx = mario->GetPosition().x < position.x ? -1 : 1;
			vx = nx * abs(vx);
			SetState(GOOMBA_STATE_WALKING);
			timer->SetDuration(TIME_GOOMBA_WAIT_TO_JUMP_LOW);
			timer->Start();
			jump_step = 2;
			break;
		case 2:
			timer->Stop();
			SetState(GOOMBA_STATE_JUMP_LOW);
			timer->SetDuration(TIME_GOOMBA_WAIT_TO_JUMP_HIGH);
			timer->Start();
			jump_step = 3;
			break;
		case 3:
			timer->Stop();
			SetState(GOOMBA_STATE_JUMP_LOW);
			timer->SetDuration(TIME_GOOMBA_WAIT_TO_JUMP_HIGH);
			timer->Start();
			jump_step = 4;
			break;
		case 4:
			timer->Stop();
			SetState(GOOMBA_STATE_JUMP_LOW);
			timer->SetDuration(TIME_GOOMBA_WAIT_TO_JUMP_HIGH);
			timer->Start();
			jump_step = 5;
			break;
		case 5:
			timer->Stop();
			SetState(GOOMBA_STATE_JUMP_HIGH);
			jump_step = 6;
			break;
		case 6:
			jump_step = 1;
			break;
		default:
			break;
		}
	}
}
int CRedWingGoomba::IsCollidable() {
	if (state == GOOMBA_STATE_DIE_BY_ATTACK) {
		return 0;
	}
	return 1;
}

void CRedWingGoomba::Render()
{
	Vec2 transformation = { 1.0f, 1.0f };
	switch (state)
	{
	case GOOMBA_STATE_WALKING:
		if (level == RedWingGoombaLevel::RedWing) {
			ani = "ani-red-para-goomba-walk";
		}
		else {
			ani = "ani-red-goomba-walk";
		}
		break;
	case GOOMBA_STATE_JUMP_LOW:
		ani = "ani-red-para-goomba-fly";
		break;
	case GOOMBA_STATE_JUMP_HIGH:
		ani = "ani-red-para-goomba-fly";
		break;
	case GOOMBA_STATE_DIE:
		ani = "ani-red-goomba-die";
		break;
	case GOOMBA_STATE_DIE_BY_ATTACK:
		ani = "ani-red-goomba-die";
		transformation = { 1.0f, -1.0f };
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = transformation;
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	//RenderBoundingBox();
}

void CRedWingGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		vx = 0;
		vy = 0;
		die_start = GetTickCount64();
		break;
	case GOOMBA_STATE_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		is_on_ground = true;
		//this->gravity = GOOMBA_GRAVITY;
		break;
	case GOOMBA_STATE_JUMP_LOW:
		is_on_ground = false;
		vx = nx * GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_JUMP_LOW_SPEED;
		break;
	case GOOMBA_STATE_JUMP_HIGH:
		is_on_ground = false;
		vx = nx * GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_JUMP_HIGH_SPEED;
		break;
	case GOOMBA_STATE_DIE_BY_ATTACK:
		die_start = GetTickCount64();
		vy = -GOOMBA_HIT_VY;
		if (nx > 0)
		{
			vx = GOOMBA_HIT_VX;
		}
		else
		{
			vx = -GOOMBA_HIT_VX;
		}
		break;
	default:
		break;
	}
}