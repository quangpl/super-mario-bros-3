#include "Goomba.h"
#include "Brick.h"
#include "RedMushroom.h"
#include "RedWingGoomba.h"
#include "Koopas.h"
#include "SceneManager.h"
#include "SmallMario.h"
#include "BigMario.h"
#include "MarioLeaf.h"
#include "RaccoonMario.h"
#include "GreenKoopas.h"
#include "GreenMushroom.h"
BigMario::BigMario() :CMasterMario()
{
	mario->SetLevel(MarioLevel::Big);
}
void BigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMasterMario::PowerCalculator(dt);
	CMasterMario::KeyboardHandler();
	mario->SetVelocityX(mario->GetSpeed().x + mario->ax * dt);
	mario->SetVelocityY(mario->GetSpeed().y + mario->ay * dt);
	if (abs(mario->GetSpeed().x) > abs(mario->maxVx)) {
		mario->SetVelocityX(mario->maxVx);
	};

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - mario->untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		mario->untouchable_start = 0;
		mario->untouchable = 0;
	}

	CCollision::GetInstance()->Process(mario, dt, coObjects);
}

void BigMario::OnNoCollision(DWORD dt)
{
	mario->position.x += (float)mario->GetSpeed().x * dt;
	mario->position.y += (float)mario->GetSpeed().y * dt;
}

void BigMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMasterMario::OnCollisionWith(e);
	if (e->ny != 0 && !e->obj->CanThrough(mario, e->nx, e->ny))
	{
		mario->vy = 0;
		if (e->ny < 0) mario->isOnPlatform = true;
	}
	else
		if (e->nx != 0 && !e->obj->CanThrough(mario, e->nx, e->ny))
		{
			mario->vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
				this->OnHitEnermy(goomba);
			}
		}
		else // hit by Goomba
		{
			if (mario->untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
				{
					this->OnDamaged();
				}
			}
		}
	}
	else if (dynamic_cast<MarioLeaf*>(e->obj))
	{
		mario->SetPlayerState(new RaccoonMario());
		e->obj->SetActive(false);
		e->obj->isDeleted = true;
	}
	else if (dynamic_cast<CRedWingGoomba*>(e->obj))
	{
		CRedWingGoomba* redWingGoomba = dynamic_cast<CRedWingGoomba*>(e->obj);

		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (redWingGoomba->GetState() != GOOMBA_STATE_DIE && redWingGoomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{

				if (redWingGoomba->GetLevel() == RedWingGoombaLevel::RedWing) {
					redWingGoomba->SetLevel(RedWingGoombaLevel::Red);
					redWingGoomba->SetState(GOOMBA_STATE_WALKING);
					mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
					this->OnHitEnermy(redWingGoomba);
				}
				else {
					redWingGoomba->SetState(GOOMBA_STATE_DIE);
					mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
					this->OnHitEnermy(redWingGoomba);
				}
			}
		}
		else // hit by Goomba
		{
			if (redWingGoomba->GetState() != GOOMBA_STATE_DIE && redWingGoomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{
				this->OnDamaged();
			}
		}
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (brick->GetState() != BRICK_STATE_NORMAL) {
			return;
		}
		if (e->ny > 0)
		{
			brick->SetState(BRICK_STATE_HIT);
		}
	}
	else if (dynamic_cast<CRedMushroom*>(e->obj))
	{
		CRedMushroom* mushroom = dynamic_cast<CRedMushroom*>(e->obj);
		// TODO: Improve collision framework to do better
		if (mushroom->GetEatable()) {
			SetState(MARIO_STATE_TRANSFORM_SMALL_TO_BIG);
			mushroom->SetState(UP_MUSHROOM_STATE_DIE);
		}
	}
	else if (dynamic_cast<GreenMushroom*>(e->obj))
	{
		GreenMushroom* mushroom = dynamic_cast<GreenMushroom*>(e->obj);
		// TODO: Improve collision framework to do better
		if (mushroom->GetEatable()) {
			mushroom->SetState(UP_MUSHROOM_STATE_DIE);
			CEffectManager* effectManager = CEffectManager::GetInstance();
			CCoindEffect* coinEffect = new CCoindEffect(mario->position.x, mario->position.y);
			int coinEffectId = effectManager->Add(coinEffect);
			coinEffect->Start([this, coinEffectId, mushroom]() {
				CEffectManager::GetInstance()->Delete(coinEffectId);
			
				});

		}
	}
	else if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		switch (koopas->GetState())
		{
		case KOOPAS_STATE_RESPAWN:
		case KOOPAS_STATE_DIE_BY_ATTACK:
		case KOOPAS_STATE_DIE_BY_HIT:
			if (mario->holding) {
				mario->holder = koopas;
				this->SetState(MARIO_STATE_HOLDING);
				koopas->SetOwner(mario);
				return;
			}
			this->OnKickShell(koopas);
			break;
		default:
			if (e->ny < 0) {
				mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopas->SetState(KOOPAS_STATE_DIE_BY_ATTACK);
				this->OnHitEnermy(koopas);
			}
			else {
				if (mario->untouchable == 0)
				{
					this->OnDamaged();
				}
			}
			break;
		}
	}

	else if (dynamic_cast<GreenKoopas*>(e->obj))
	{
		GreenKoopas* koopas = dynamic_cast<GreenKoopas*>(e->obj);
		switch (koopas->GetState())
		{
			// TODO: Improve collision framework to make it easier
		case KOOPAS_STATE_RESPAWN:
		case KOOPAS_STATE_DIE_BY_ATTACK:
		case KOOPAS_STATE_DIE_BY_HIT:
			if (mario->holding) {
				mario->holder = koopas;
				this->SetState(MARIO_STATE_HOLDING);
				koopas->SetOwner(mario);
				return;
			}
			this->OnKickShell(koopas);
			break;
		default:
			if (e->ny < 0) {
				mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopas->SetState(KOOPAS_STATE_DIE_BY_ATTACK);
				this->OnHitEnermy(koopas);
			}
			else {
				if (mario->untouchable == 0)
				{
					this->OnDamaged();
				}
			}
			break;
		}
	}
}


void BigMario::Render()
{
	bool has_holding = mario->holder != NULL;

	if (!mario->isOnPlatform)
	{
		ani = "ani-big-mario-jump";
	}
	else
	{
		if (mario->vx == 0)
		{
			ani = "ani-big-mario-idle";
		}
		else {
			ani = "ani-big-mario-walk";
			if (abs(mario->vx) >= MARIO_RUNNING_SPEED) {
				ani = "ani-big-mario-high-speed";
			}
			if (mario->vx * mario->ax < 0)// trai dau
			{
				mario->SetNx(mario->vx > 0 ? 1 : -1);
				ani = "ani-big-mario-skid";
			}

		}
	}

	if (has_holding)
	{
		ani = mario->vx == 0 ? "ani-big-mario-hold-idle" : "ani-big-mario-hold";
	}
	if (mario->isSitting)
	{
		if (!CGame::GetInstance()->IsKeyDown(DIK_LEFT) && !CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {
			ani = "ani-big-mario-crouch";
		}

	}
	if (mario->GetState() == MARIO_STATE_WARP_VERTICAL) {
		ani = "ani-big-mario-idle-front";
	}

	if (ani.compare("") == 0) ani = "ani-big-mario-idle";

	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2(mario->GetNx() * 1.0f, 1.0f);
	CAnimations::GetInstance()->Get(ani)->Render(mario->position.x, mario->position.y);
}

void BigMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RELEASE_RUNNING:
		mario->ax = 0;
		break;
	case MARIO_STATE_RUNNING:
		if (mario->isSitting) break;
		mario->maxVx = mario->GetNx() * MARIO_RUNNING_SPEED;
		mario->ax = mario->GetNx() * MARIO_ACCEL_RUN_X;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		//if (mario->isSitting) break;
		if (mario->isSitting) {
			mario->SetPosition(Vec2{ mario->position.x, mario->position.y - abs(MARIO_BIG_CROUCH_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) * 3 });
			mario->isSitting = false;
		}
		mario->maxVx = MARIO_WALKING_SPEED;
		mario->ax = MARIO_ACCEL_WALK_X;
		mario->SetNx(1);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (mario->isSitting) {
			mario->SetPosition(Vec2{ mario->position.x, mario->position.y - abs(MARIO_BIG_CROUCH_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) * 3 });
			mario->isSitting = false;
		}
		//if (mario->isSitting) break;
		mario->maxVx = -MARIO_WALKING_SPEED;
		mario->ax = -MARIO_ACCEL_WALK_X;
		mario->SetNx(-1);
		break;
	case MARIO_STATE_JUMP:
		if (mario->isSitting) break;
		if (mario->isOnPlatform)
		{
			if (abs(mario->GetSpeed().x) == MARIO_RUNNING_SPEED)
				mario->vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				mario->vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (mario->vy < 0) mario->vy += MARIO_JUMP_SPEED_Y / 2;
		break;
	case MARIO_STATE_IDLE:
		mario->ax = 0;
		if (mario->vx > 0) {
			mario->vx = mario->vx - MARIO_DECREASE_SPEED;
			if (mario->vx < 0)
			{
				mario->vx = 0;
			}
		}
		else if (mario->vx < 0) {
			mario->vx = mario->vx + MARIO_DECREASE_SPEED;
			if (mario->vx > 0)
			{
				mario->vx = 0;
			}
		}
		break;

	case MARIO_STATE_DIE:
		mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
		if (mario->vx > 0) {
			mario->SetNx(1);
		}
		else {
			mario->SetNx(-1);
		}
		mario->vx = 0;
		mario->ax = 0;
		break;
	case MARIO_STATE_HOLDING:
		mario->holding = true;
		break;
	case MARIO_STATE_RELEASE_HOLDING:
		this->OnReleaseHolding();
		break;
	case MARIO_STATE_TRANSFORM_SMALL_TO_BIG:
		//transformation_start = GetTickCount64();
		mario->vx = 0;
		mario->vy = 0;
		break;
	case MARIO_STATE_SIT:
		if (mario->holding) {
			return;
		}
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT) || CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {
			return;
		}
		if (mario->isOnPlatform)
		{
			state = MARIO_STATE_IDLE;
			mario->isSitting = true;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (mario->isSitting)
		{
			mario->isSitting = false;
			state = MARIO_STATE_IDLE;
			mario->position.y -= MARIO_SIT_HEIGHT_ADJUST * 3;
		}
		break;

	}

	mario->SetState(state);
}

void BigMario::OnKeyUp(int KeyCode) {
	//DebugOut(L"On key up %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		this->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		if (mario->GetHolding()) {
			this->SetState(MARIO_STATE_RELEASE_HOLDING);
		}
		this->SetState(MARIO_STATE_RELEASE_RUNNING);
		break;
		/*case DIK_Z:
			this->SetState(MARIO_STATE_RELEASE_HOLDING);
			break;*/
	case DIK_DOWN:
		this->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void BigMario::OnKeyDown(int KeyCode) {
	//DebugOut(L"On key down %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		//this->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		this->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_0:
		this->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}


RectBox BigMario::GetBoundingBox() {
	RectBox bounding_box = RectBox(0, 0, 0, 0);
	int height = mario->isSitting ? MARIO_BIG_CROUCH_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT;
	bounding_box.left = mario->position.x - MARIO_BIG_BBOX_WIDTH * 3 / 2;
	bounding_box.top = mario->position.y - height * 3 / 2;
	bounding_box.right = bounding_box.left + MARIO_BIG_BBOX_WIDTH * 3;
	bounding_box.bottom = bounding_box.top + height * 3;
	return bounding_box;
}
