#include "Goomba.h"

CGoomba::CGoomba(int level) :CGameObject(x, y)
{
	this->level = level;
	this->gravity = GOOMBA_GRAVITY;
	timer = new CTimer(0);
	die_start = -1;
	if (nx > 0) {
		nx *= -1;
	}
	if (level == GoombaLevel::Nomal) {
		SetState(GOOMBA_STATE_WALKING);
	}
	else if (level == GoombaLevel::RedWing) {
		jump_step = 1;
		SetState(GOOMBA_STATE_WALKING);
	}
	else {
		DebugOut(L"Invalid Goomba Type");
	}
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = top = right = bottom = 0;
		return;
	}
	switch (level)
	{
	case GoombaLevel::Nomal:
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
		break;
	}
	case GoombaLevel::RedWing:
	case GoombaLevel::Red:
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	default:
		break;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	if (e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) {
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);
		//DebugOut(L"vx: %f, vy: %f", vx, vy);
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += (this->gravity * dt);
	if ((state == GOOMBA_STATE_DIE && GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	CMario* mario = CMario::GetInstance();
	if (level != GoombaLevel::RedWing) {
		return;
	}
	if (timer->IsRunning() && !timer->IsTimeUp()) {
		return;
	}
	if (is_on_ground && jump_step !=0) {
		switch (jump_step)
		{
		case 1:
			nx = mario->GetPositionX() < x ? -1 : 1;
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
int CGoomba::IsCollidable() {
	if (state == GOOMBA_STATE_DIE_BY_ATTACK) {
		return 0;
	}
	return 1;
}

void CGoomba::Render()
{
	if (level == GoombaLevel::Nomal) {
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = GOOMBA_ANI_WALKING;
			break;
		case GOOMBA_STATE_DIE:
			ani = GOOMBA_ANI_DIE;
			break;
		case GOOMBA_STATE_DIE_BY_ATTACK:
			ani = GOOMBA_ANI_DIE_BY_ATTACK;
			break;
		default:
			break;
		}
	}
	else if (level == GoombaLevel::Red) {
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = GOOMBA_RED_ANI_WALKING;
			break;
		case GOOMBA_STATE_DIE:
			ani = GOOMBA_RED_ANI_DIE_BY_CRUSH;
			break;
		default:
			break;
		}
	}
	else {
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = GOOMBA_WING_RED_ANI_WALKING;
			break;
		case GOOMBA_STATE_JUMP_LOW:
			ani = GOOMBA_WING_RED_ANI_JUMP_LOW;
			break;
		case GOOMBA_STATE_JUMP_HIGH:
			ani = GOOMBA_WING_RED_ANI_JUMP_HIGH;
			break;
		default:
			break;
		}
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		this->gravity = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		is_on_ground = true;
		y = y - (RED_PARA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT)/2;
		break;
	case GOOMBA_STATE_JUMP_LOW:
		is_on_ground = false;
		//vx = nx * GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_JUMP_LOW_SPEED;
		break;
	case GOOMBA_STATE_JUMP_HIGH:
		is_on_ground = false;
		//vx = nx * GOOMBA_WALKING_SPEED;
		vy = -2 * GOOMBA_JUMP_LOW_SPEED;
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
