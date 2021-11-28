#include "RedGoomba.h"

CRedGoomba* CRedGoomba::Create(Vec2 position) {
	CRedGoomba* goomba = new CRedGoomba();
	goomba->SetPosition(Vec2(position.x, position.y - 50));
	return goomba;
}

CRedGoomba::CRedGoomba() :CGameObject()
{
	this->jump_step = 1;
	this->gravity = GOOMBA_GRAVITY;
	if (nx > 0) {
		nx *= -1;
	}
	this->timer = new CTimer(0);
	SetState(GOOMBA_STATE_WALKING);
}

RectBox CRedGoomba::GetBoundingBox() {
	this->bounding_box.left = position.x - GOOMBA_BBOX_WIDTH / 2;
	this->bounding_box.top = position.y - GOOMBA_BBOX_HEIGHT / 2;
	this->bounding_box.right = this->bounding_box.left + GOOMBA_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + GOOMBA_BBOX_HEIGHT;
	return this->bounding_box;
}

void CRedGoomba::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void CRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
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
}

void CRedGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	if (e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) {
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

void CRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += (this->gravity * dt);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	CMario* mario = CMario::GetInstance();
	if (timer->IsRunning() && !timer->IsTimeUp()) {
		return;
	}
	if (is_on_ground) {
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
int CRedGoomba::IsCollidable() {
	if (state == GOOMBA_STATE_DIE_BY_ATTACK) {
		return 0;
	}
	return 1;
}

void CRedGoomba::Render()
{
	if (level == GoombaLevel::Red) {
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = "ani-red-goomba-walk";
			break;
		case GOOMBA_STATE_DIE:
			ani = "ani-red-goomba-die";
			break;
		default:
			break;
		}
	}
	else {
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = "ani-red-para-goomba-walk";
			break;
		case GOOMBA_STATE_JUMP_LOW:
			ani = "ani-red-para-goomba-fly";
			break;
		case GOOMBA_STATE_JUMP_HIGH:
			ani = "ani-red-para-goomba-fly";
			break;
		default:
			break;
		}
	}
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	//RenderBoundingBox();
}

void CRedGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		vx = 0;
		vy = 0;
		this->gravity = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		is_on_ground = true;
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
		vy = -GOOMBA_HIT_SPEED;
		if (nx > 0)
		{
			vx = MARIO_WALKING_SPEED;
		}
		else
		{
			vx = -MARIO_WALKING_SPEED;
		}
		break;
	default:
		break;
	}
}