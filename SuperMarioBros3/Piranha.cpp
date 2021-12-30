#include "Piranha.h"
#include "Mario.h"
#include "EffectManager.h"
#include "Tail.h"
#include "MarioDamagedEffect.h"
#include "Koopas.h"
#include "GreenKoopas.h"

Piranha::Piranha(Vec2 _pos) :CGameObject()
{
	stopwatch = new Stopwatch();
	this->ownerPos = _pos;
	this->position = _pos;
	stopwatch->Start();
	zIndex = 8;
	SetState(PIRANHA_STATE_DISPLAY);
}


RectBox Piranha::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + PIRANHA_SIZE_X;
	this->bounding_box.bottom = this->bounding_box.top + PIRANHA_SIZE_Y;
	return this->bounding_box;
}

void Piranha::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void Piranha::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTail*>(e->obj) || (dynamic_cast<CKoopas*>(e->obj) && e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) || (dynamic_cast<GreenKoopas*>(e->obj) && e->obj->GetState() == KOOPAS_STATE_DIE_MOVE)) {
		this->SetDeleted(true);
		// disable fireball
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CMarioDamagedEffect* damagedEffect = new CMarioDamagedEffect(this->position, this->GetNx());
		int effectId = effectManager->Add(damagedEffect);
		damagedEffect->Start([this, effectId]() {
			CEffectManager::GetInstance()->Delete(effectId);
			});
	}
}


void Piranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == PIRANHA_STATE_DISPLAY)
	{
		switch (movingStep)
		{
		case 0:
		{
			position.y -= VENUS_SPEED * dt;
			if (ownerPos.y - position.y >= PIRANHA_SIZE_Y)
			{
				position.y = ownerPos.y - PIRANHA_SIZE_Y;
				movingStep = 1;
				stopwatch->Restart();
			}
			collidable = true;
		}
		break;
		case 1:
		{
			if (stopwatch->Elapsed() > VENUS_WAIT_TIME)
			{
				stopwatch->Restart();
				movingStep = 2;
			}
		}
		break;
		case 2:
		{
			position.y += VENUS_SPEED * dt;
			if (position.y > ownerPos.y)
			{
				position.y = ownerPos.y;
				movingStep = 3;
				stopwatch->Restart();
				TrackPlayerPosition();
				collidable = false;
			}
		}
		break;
		case 3:
		{
			if (stopwatch->Elapsed() > VENUS_WAIT_TIME)
			{
				stopwatch->Restart();
				movingStep = 0;
			}
		}
		break;
		}
	}
	else {
		TrackPlayerPosition();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int Piranha::IsCollidable() {
	return collidable;
}

void Piranha::TrackPlayerPosition()
{
	CMario* mario = CMario::GetInstance();
	if (!mario) return;

	Vec2 marioPos = mario->GetPosition();

	auto distance = abs(marioPos.x - position.x);
	if (distance < VENUS_HIDE_DISTANCE && state == PIRANHA_STATE_DISPLAY)
	{
		state = PIRANHA_STATE_HIDE;
	}
	else if (distance >= VENUS_HIDE_DISTANCE && state == PIRANHA_STATE_HIDE)
	{
		state = PIRANHA_STATE_DISPLAY;
		movingStep = 0;
		stopwatch->Restart();
	}
}

void Piranha::Render()
{
	CAnimations::GetInstance()->Get("ani-green-piranha-plant-attack")->Render(position.x + PIRANHA_SIZE_X / 2, position.y + PIRANHA_SIZE_Y / 2);
	RenderBoundingBox();
}

void Piranha::SetState(int state)
{
	CGameObject::SetState(state);
}
