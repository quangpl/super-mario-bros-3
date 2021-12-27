#include "Goomba.h"
#include "GoombaDieEffect.h"

CGoomba::CGoomba() :CGameObject()
{
	this->gravity = GOOMBA_GRAVITY;
	die_start = -1;
	if (nx > 0) {
		nx *= -1;
	}
	SetState(GOOMBA_STATE_WALKING);
}

CGoomba* CGoomba::Create(Vec2 position) {
	CGoomba* goomba = new CGoomba();
	goomba->SetPosition(Vec2(position.x, position.y - 50));
	return goomba;
}

RectBox CGoomba::GetBoundingBox() {
	int bbox_height = this->state == GOOMBA_STATE_DIE ? GOOMBA_BBOX_HEIGHT_DIE : GOOMBA_BBOX_HEIGHT;
	this->bounding_box.left = position.x - GOOMBA_BBOX_WIDTH / 2;
	this->bounding_box.top = position.y - bbox_height / 2;
	this->bounding_box.right = this->bounding_box.left + GOOMBA_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + bbox_height;
	return this->bounding_box;
}

void CGoomba::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	if (dynamic_cast<CTail*>(e->obj))
	{
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

void CGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	if (e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) {
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += (this->gravity * dt);
	/*if (((state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_DIE_BY_ATTACK) && GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}*/
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
int CGoomba::IsCollidable() {
	if (state == GOOMBA_STATE_DIE_BY_ATTACK) {
		return 0;
	}
	return 1;
}

void CGoomba::Render()
{
	Vec2 transformation = { 1.0f, 1.0f };
	ani = "ani-goomba-walk";

	if (state == GOOMBA_STATE_DIE) {
		this->SetDeleted(true);
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CGoombaDieEffect* goombaDieEffect = new CGoombaDieEffect(this->position, this->GetNx());
		int effectId = effectManager->Add(goombaDieEffect);
		goombaDieEffect->Start([this, effectId]() {
			CEffectManager::GetInstance()->Delete(effectId);

			});
	}
	if (state == GOOMBA_STATE_DIE_BY_ATTACK) {
		ani = "ani-goomba-die";
		transformation = { 1.0f, -1.0f };
	}
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = transformation;
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
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
