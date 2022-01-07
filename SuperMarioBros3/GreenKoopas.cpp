#include "GreenKoopas.h"
#include "KoopasRadar.h"
#include "RedWingGoomba.h"

GreenKoopas::GreenKoopas() :CGameObject()
{
	//type = Type::KOOPAS;
	this->revivalStopWatch = new Stopwatch();
	koopas_type = KoopaType::RedTroopa;
	SetState(KOOPAS_STATE_WALKING);
	this->gravity = KOOPAS_GRAVITY;
}

int GreenKoopas::IsCollidable() {
	if (state == KOOPAS_STATE_DIE) {
		return 0;
	}
	return 1;
}
bool GreenKoopas::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	if (dynamic_cast<GreenKoopas*>(gameObjToCollide) && gameObjToCollide->GetState() == KOOPAS_STATE_WALKING) {
		return true;
	}
	else {
		return false;
	}
 }

RectBox GreenKoopas::GetBoundingBox() {
	bounding_box.left = position.x - size.x / 2;
	bounding_box.top = position.y - size.y / 2;
	bounding_box.right = bounding_box.left + size.x;
	bounding_box.bottom = bounding_box.top + size.y;
	return this->bounding_box;
}
void GreenKoopas::OnBlockingOnY(int jetY)
{

};
void GreenKoopas::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
	isOnPlatForm = false;
};

GreenKoopas* GreenKoopas::Create(Vec2 pos, bool _canJump) {
	GreenKoopas* greenkoopas = new GreenKoopas();
	greenkoopas->canJump = _canJump;
	RectBox bounding_box = greenkoopas->GetBoundingBox();
	greenkoopas->SetPosition(Vec2(pos.x, pos.y - (bounding_box.bottom - bounding_box.top) / 2));
	return greenkoopas;
}
void GreenKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->CanThrough(this, e->nx, e->ny)) return;
	if (e->ny != 0)
	{
		if (e->ny < 0) {
			isOnPlatForm = true;
		}
		vy = 0;
		if (state == KOOPAS_STATE_DIE_BY_HIT) {
			vx = 0;
		}
	}
	else if (e->nx != 0)
	{
		if (!(dynamic_cast<CKoopas*>(e->obj) || dynamic_cast<CMario*>(e->obj) || dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<GreenKoopas*>(e->obj) || dynamic_cast<CRedWingGoomba*>(e->obj))) {
			nx = -nx;
		}
	}

	if (dynamic_cast<CBrick*>(e->obj)) {
		OnCollisionWithBrick(e);
	}
	else if (dynamic_cast<CTail*>(e->obj) && CMario::GetInstance()->isAttacking) {
		transformation = Vec2{ 1.0f,-1.0f };
		this->SetState(KOOPAS_STATE_DIE_BY_HIT);
	}
	else if (dynamic_cast<GreenKoopas*>(e->obj) && this->state == KOOPAS_STATE_DIE_MOVE) {
		transformation = Vec2{ 1.0f,-1.0f };
		e->obj->SetState(KOOPAS_STATE_DIE);
	}
	else if (dynamic_cast<CKoopas*>(e->obj) && this->state == KOOPAS_STATE_DIE_MOVE) {
		transformation = Vec2{ 1.0f,-1.0f };
		e->obj->SetState(KOOPAS_STATE_DIE);
	}
}

void GreenKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (state == KOOPAS_STATE_DIE_MOVE && e->obj->GetState() != BRICK_STATE_BROKEN) {
		e->obj->SetState(BRICK_STATE_BROKEN);
	}
}

void GreenKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive) {
		return;
	}
	if (state == KOOPAS_STATE_DIE && GetTickCount64() - die_start >= 1000) {
		isActive = false;
		this->isDeleted = true;
	}
	if (isOnPlatForm && canJump && state == KOOPAS_STATE_WALKING) {
		vy = -GREEN_KOOPAS_JUMP_SPEED;
	}
	vx = nx * abs(vx);
	// Switch case for each owner type
	if (this->owner != NULL && dynamic_cast<CMario*>(this->owner)) {
		CMario* mario = dynamic_cast<CMario*>(this->owner);
		int marioDirection = mario->vx > 0 ? 1 : -1;
		position.x = this->owner->GetPosition().x + marioDirection * (mario->GetBoundingBox().right - mario->GetBoundingBox().left);
		position.y = this->owner->GetPosition().y;
	}
	else {
		vy += (KOOPAS_GRAVITY * dt);
	}
	if ((state == KOOPAS_STATE_DIE_BY_ATTACK || state == KOOPAS_STATE_DIE_BY_HIT) && shell_step == 0 && revivalStopWatch->Elapsed() >= KOOPAS_CROUCH_TO_REPAWN_TIME) {
		shell_step = 1;
		this->SetState(KOOPAS_STATE_RESPAWN);
		revivalStopWatch->Restart();
	}
	if (state == KOOPAS_STATE_RESPAWN && shell_step == 1 && revivalStopWatch->Elapsed() >= KOOPAS_RESPAWN_TO_REVIVAL_TIME) {
		SetState(KOOPAS_STATE_WALKING);
		shell_step = 0;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void GreenKoopas::Render()
{
	switch (state)
	{
	case KOOPAS_STATE_DIE_BY_HIT:
	case KOOPAS_STATE_DIE_BY_ATTACK:
		ani = "ani-green-koopa-troopa-shell-idle";
		break;
	case KOOPAS_STATE_DIE_MOVE:
		ani = "ani-green-koopa-troopa-shell-run";
		break;
	case KOOPAS_STATE_IDLE:
		ani = "ani-green-koopa-troopa-shell-idle";
		break;
	case KOOPAS_STATE_RESPAWN:
		ani = "ani-green-koopa-troopa-respawning";
		break;
	case KOOPAS_STATE_WALKING:
	case KOOPAS_STATE_WALKING_DOWN:
		ani = "ani-green-koopa-troopa-move";
		break;
	case KOOPAS_STATE_DIE:
		ani = "ani-green-koopa-troopa-crouch";
		transformation = { 1.0f, -1.0f };
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2((float)-nx, transformation.y);
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	RenderBoundingBox();
}

void GreenKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		this->vx = nx * KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_RESPAWN:
		nx = CMario::GetInstance()->GetPosition().x < position.x ? -1 : 1;
		transformation = Vec2{ nx * 1.0f, 1.0f };
		break;
	case KOOPAS_STATE_DIE_BY_ATTACK:
		this->revivalStopWatch->Restart();
		position.y = position.y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		this->vx = 0;
		break;
	case KOOPAS_STATE_DIE_BY_HIT:
		canJump = false;
		this->revivalStopWatch->Restart();
		position.y = position.y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		vy = -KOOPAS_HIT_VY;
		nx = CMario::GetInstance()->GetNx();
		vx = KOOPAS_HIT_VX * nx;
		break;
	case KOOPAS_STATE_DIE_MOVE:
		position.y = position.y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		//nx = CMario::GetInstance()->GetNx();
		this->SetVelocityX(nx * KOOPAS_SHELL_RUN_SPEED);
		break;
	case KOOPAS_STATE_DIE:
		die_start = GetTickCount64();
		vy = -KOOPAS_HIT_VY;
		if (nx > 0)
		{
			vx = 0.2f;
		}
		else
		{
			vx = -0.2f;
		}
		break;
	default:
		break;
	}
}
