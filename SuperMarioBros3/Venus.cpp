#include "Venus.h"
#include "Mario.h"
#include "Tail.h"
#include "MarioDamagedEffect.h"
#include "Koopas.h"
#include "GreenKoopas.h"

Venus::Venus(Vec2 _pos, int type) :CGameObject()
{
	this->shootStopwatch = new Stopwatch();
	this->movingStopwatch = new Stopwatch();
	this->ownerPos = _pos;
	this->position = _pos;
	this->shootStopwatch->Start();
	this->movingStopwatch->Start();
	this->type = type;
	zIndex = 8;
	SetState(VENUS_STATE_DISPLAY);
	for (int i = 0; i < 2; i++) { // num of fireball
		Fireball* ball = new Fireball();
		ball->SetDeleted(true);
		fireballs.push_back(ball);
	}
}


RectBox Venus::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + VENUS_SIZE_X;
	this->bounding_box.bottom = this->bounding_box.top + VENUS_SIZE_Y;
	return this->bounding_box;
}

void Venus::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
};

void Venus::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTail*>(e->obj) || (dynamic_cast<CKoopas*>(e->obj) && e->obj->GetState() == KOOPAS_STATE_DIE_MOVE) || (dynamic_cast<GreenKoopas*>(e->obj) && e->obj->GetState() == KOOPAS_STATE_DIE_MOVE)) {
		this->SetDeleted(true);
		// disable fireball

		for (Fireball* fireball : fireballs)
		{
			fireball->active = false;
			fireball->SetDeleted(true);
		}

		CEffectManager* effectManager = CEffectManager::GetInstance();
		CMarioDamagedEffect* damagedEffect = new CMarioDamagedEffect(this->position, this->GetNx());
		int effectId = effectManager->Add(damagedEffect);
		damagedEffect->Start([this, effectId]() {
			CEffectManager::GetInstance()->Delete(effectId);
			});
	}
}


void Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == VENUS_STATE_DISPLAY)
	{
		switch (movingStep)
		{
		case 0:
		{
			position.y -= VENUS_SPEED * dt;
			if (ownerPos.y - position.y >= VENUS_SIZE_Y)
			{
				position.y = ownerPos.y - VENUS_SIZE_Y;
				movingStep = 1;
				movingStopwatch->Restart();

				targetLocking = true;
				shootStopwatch->Restart();
			}
			collidable = true;
		}
		break;
		case 1:
		{
			if (movingStopwatch->Elapsed() > VENUS_WAIT_TIME)
			{
				movingStopwatch->Restart();
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
				movingStopwatch->Restart();
				RefindMario();
				collidable = false;
			}
		}
		break;
		case 3:
		{
			if (movingStopwatch->Elapsed() > VENUS_WAIT_TIME)
			{
				movingStopwatch->Restart();
				movingStep = 0;
			}
		}
		break;
		}
	}
	else {
		RefindMario();
	}
	CMario* mario = CMario::GetInstance();
	Vec2 marioPos = mario->GetPosition();

	if (movingStep <= 1) {
		nx = marioPos.x < position.x ? -1 : 1;
		if (!targetLocking) direction = marioPos.y < position.y ? -1 : 1;
	}

	if (targetLocking && this->shootStopwatch->Elapsed() > VENUS_SHOOT_WAIT_TIME) {
		shootStopwatch->Restart();
		targetLocking = false;

		for (Fireball* fireball : fireballs)
		{
			if (!fireball->active) {
				if (fireball->spawned) {
					fireball->active = true;
				}
				fireball->SetDeleted(false);
				fireball->Shoot(GetBoundingBox(), nx);
				Vec2 fireballPosition = fireball->GetPosition();

				RectBox cam = SceneManager::GetInstance()->GetActiveScene()->GetCamera()->GetBoundingBox();

				if (fireballPosition.x >= cam.left && fireballPosition.y >= cam.top && fireballPosition.x <= cam.right && fireballPosition.y <= cam.bottom) {
					if (!fireball->spawned) {
						SceneManager::GetInstance()->GetActiveScene()->AddObject(fireball);
						fireball->spawned = true;
						fireball->active = true;
					}
					break;
				}
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int Venus::IsCollidable() {
	return collidable;
}
void Venus::OnGoingToCamera() {
	for (Fireball* fireball : fireballs)
	{
		if (fireball->IsDeleted()) {
			this->shootStopwatch->Restart();
			this->movingStopwatch->Restart();
			collidable = true;
			state = VENUS_STATE_DISPLAY;
			targetLocking = 1;
			movingStep = 0;
			direction = 1;
			position = ownerPos;
			break;
		}
	}
}
void Venus::RefindMario()
{
	CMario* mario = CMario::GetInstance();
	if (!mario) return;

	Vec2 marioPos = mario->GetPosition();
	nx = marioPos.x < position.x ? -1 : 1;
	auto distance = abs(marioPos.x - position.x);
	if (distance < VENUS_HIDE_DISTANCE && state == VENUS_STATE_DISPLAY)
	{
		state = VENUS_STATE_HIDE;
	}
	else if (distance >= VENUS_HIDE_DISTANCE && state == VENUS_STATE_HIDE)
	{
		state = VENUS_STATE_DISPLAY;
		movingStep = 0;
		movingStopwatch->Restart();
	}
}

void Venus::Render()
{
	string color = type == VenusType::GreenVenus ? "green" : "red";
	switch (movingStep)
	{
	case 0:
	case 2:
		ani = direction < 0 ? "ani-" + color + "-venus-fire-trap-headup" : "ani-" + color + "-venus-fire-trap-headdown";
		break;
	case 1:
	case 3:
		ani = direction < 0 ? "ani-" + color + "-venus-fire-trap-headup-idle" : "ani-" + color + "-venus-fire-trap-headdown-idle";
		break;
	}

	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale.x = (float)-nx;
	CAnimations::GetInstance()->Get(ani)->Render(position.x + VENUS_SIZE_X / 2, position.y + VENUS_SIZE_Y / 2);
	RenderBoundingBox();
}

void Venus::SetState(int state)
{
	CGameObject::SetState(state);
}
