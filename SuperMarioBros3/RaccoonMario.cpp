#include "Goomba.h"
#include "Brick.h"
#include "RedMushroom.h"
#include "RedWingGoomba.h"
#include "Koopas.h"
#include "SceneManager.h"
#include "SmallMario.h"
#include "BigMario.h"
#include "RaccoonMario.h"


RaccoonMario::RaccoonMario() :CMasterMario()
{
	this->tail = new CTail(mario);
	stopwatch = new Stopwatch();
	flyStopwatch = new Stopwatch();
	this->tail->hitTime = MARIO_TAIL_HIT_TIME;
	SceneManager::GetInstance()->GetActiveScene()->AddObject(this->tail);
}

void RaccoonMario::KeyboardHandler() {
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT)) {
		if (game->IsKeyDown(DIK_A))
			this->SetState(MARIO_STATE_RUNNING);
		else
			this->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (game->IsKeyDown(DIK_A))
			this->SetState(MARIO_STATE_RUNNING);
		else
			this->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else {
		if (mario->isOnPlatform) {
			this->SetState(MARIO_STATE_IDLE);
		}
		else {
			if (mario->vy > 0 && game->IsKeyDown(DIK_S)) {
				this->SetState(MARIO_STATE_FLOAT);
			}
		}
	}
}

void RaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->KeyboardHandler();
	PowerCalculator(dt);
	if (mario->isAttacking && stopwatch->Elapsed() >= TAIL_TIMEOUT) {
		this->SetState(MARIO_STATE_RELEASE_ATTACK);
	}
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

void RaccoonMario::OnNoCollision(DWORD dt)
{
	mario->position.x += mario->GetSpeed().x * dt;
	mario->position.y += mario->GetSpeed().y * dt;
}

void RaccoonMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
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
			}
		}
		else // hit by Goomba
		{
			if (mario->untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
				{
					mario->StartUntouchable();
					mario->SetPlayerState(new SmallMario());
				}
			}
		}
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
				}
				else {
					redWingGoomba->SetState(GOOMBA_STATE_DIE);
					mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
			}
		}
		else // hit by Goomba
		{
			if (redWingGoomba->GetState() != GOOMBA_STATE_DIE && redWingGoomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{
				mario->StartUntouchable();
				mario->SetPlayerState(new SmallMario());
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
	else if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		switch (koopas->GetState())
		{
			// TODO: Improve collision framework to make it easier
		case KOOPAS_STATE_RESPAWN:
		case KOOPAS_STATE_DIE_BY_ATTACK:
			if (mario->holding) {
				mario->holder = koopas;
				this->SetState(MARIO_STATE_HOLDING);
				koopas->SetOwner(mario);
				return;
			}
			koopas->SetState(KOOPAS_STATE_DIE_MOVE);
			break;
		default:
			if (e->ny < 0) {
				mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopas->SetState(KOOPAS_STATE_DIE_BY_ATTACK);
			}
			else {
				if (mario->untouchable == 0)
				{
					mario->StartUntouchable();
					mario->SetPlayerState(new SmallMario());
				}
			}
			break;
		}
	}
}


void RaccoonMario::Render()
{
	bool has_holding = mario->holder != NULL;

	if (!mario->isOnPlatform)
	{
		if (flyStopwatch->IsRunning())
		{
			ani = "ani-raccoon-mario-fly";
		}
		if (mario->vy > 0)
		{
			ani = "ani-raccoon-mario-fall";
		}
		if (mario->isJumping == true)
		{
			ani = "ani-raccoon-mario-jump";
		}
		if (mario->GetState() == MARIO_STATE_FLOAT)
		{
			ani = "ani-raccoon-mario-float";
		}
	}
	else
	{
		if (mario->vx == 0)
		{
			ani = "ani-raccoon-mario-idle";
			if (has_holding) {
				ani = "ani-raccoon-mario-hold-idle";
			}
		}
		else if (mario->vx > 0)
		{
			if (mario->ax < 0)
			{
				mario->SetNx(1);
				ani = "ani-raccoon-mario-skid";
			}
			else if (mario->vx >= MARIO_RUNNING_SPEED)
				ani = "ani-raccoon-mario-speed-up";
			else
				ani = "ani-raccoon-mario-walk";
			if (has_holding) {
				ani = "ani-raccoon-mario-hold";
			}
		}
		else // vx < 0
		{
			if (mario->ax > 0)
			{
				mario->SetNx(-1);
				ani = "ani-raccoon-mario-skid";
			}
			else if (mario->vx <= -MARIO_RUNNING_SPEED)
				ani = "ani-raccoon-mario-speed-up";
			else
				ani = "ani-raccoon-mario-walk";
			if (has_holding) {
				ani = "ani-raccoon-mario-hold";
			}
		}
		if (mario->isSitting)
		{
			ani = "ani-raccoon-mario-crouch";
		}
		if (mario->isAttacking)
		{
			ani = "ani-raccoon-mario-spin";
		}
		if (mario->GetState() == MARIO_STATE_WARP_VERTICAL) {
			ani = "ani-raccoon-mario-idle-front";
		}
	}


	if (ani.compare("") == 0) ani = "ani-raccoon-mario-idle";

	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2(mario->GetNx() * 1.0f, 1.0f);
	CAnimations::GetInstance()->Get(ani)->Render(mario->position.x, mario->position.y);
	mario->RenderBoundingBox();
}

void RaccoonMario::PowerCalculator(DWORD dt) {
	float maxRun = abs(mario->vx) > MARIO_RUNNING_SPEED * 0.85f;

	if (maxRun && mario->isOnPlatform)
	{
		mario->SetPower(max(0.0f, min(mario->GetPower() + PMETER_UP_STEP * dt, PMETER_MAX + 0.2f)));
	}
	else {
		if (flyStopwatch->IsRunning()) {
			if (flyStopwatch->Elapsed() >= 4000) {
				mario->SetPower(0);
				flyStopwatch->Stop();
			}
		}
		else {
			if (mario->GetPower() > 0)
				mario->SetPower(max(0.0f, min(mario->GetPower() - PMETER_DOWN_STEP * dt, PMETER_MAX)));
		}
	}
}

void RaccoonMario::SetState(int state)
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
		if (mario->isSitting) break;
		mario->maxVx = MARIO_WALKING_SPEED;
		mario->ax = MARIO_ACCEL_WALK_X;
		mario->SetNx(1);
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (mario->isSitting) break;
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
			mario->isJumping = true;
		}
		break;
	case MARIO_STATE_FLY:
		break;
	case MARIO_STATE_FLOAT:
		SceneManager::GetInstance()->GetActiveScene()->GetCamera()->ResetLimitEdge();
		mario->vy = MARIO_FLOATING_SPEED;
		break;
	case MARIO_STATE_RELEASE_JUMP:
		//if (mario->vy < 0) mario->vy += MARIO_JUMP_SPEED_Y / 2;
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
	case MARIO_STATE_RELEASE_ATTACK:
		mario->isAttacking = false;
		stopwatch->Restart();
		break;
	case MARIO_STATE_ATTACK:
		if (!mario->isAttacking) {
			stopwatch->Restart();
			mario->isAttacking = true;
			tail->SetDeleted(false);
			SceneManager::GetInstance()->GetActiveScene()->AddObject(tail);
			tail->Attack();
		}
		break;
	case MARIO_STATE_RELEASE_HOLDING:
		mario->holding = false;
		if (mario->holder != NULL) {
			if (dynamic_cast<CKoopas*>(mario->holder)) {
				CKoopas* koopas = dynamic_cast<CKoopas*>(mario->holder);
				koopas->SetOwner(NULL);
				koopas->SetNx(mario->GetNx());
				koopas->SetState(KOOPAS_STATE_DIE_MOVE);
			}
			mario->holder = NULL;
		}
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
		if (mario->isOnPlatform)
		{
			state = MARIO_STATE_IDLE;
			mario->isSitting = true;
			mario->vx = 0;
			mario->vy = 0.0f;
			//mario->position.y += MARIO_SIT_HEIGHT_ADJUST * 3;
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

void RaccoonMario::OnKeyUp(int KeyCode) {
	DebugOut(L"On key up %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		this->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		this->SetState(MARIO_STATE_RELEASE_RUNNING);
		break;
	case DIK_Z:
		this->SetState(MARIO_STATE_RELEASE_HOLDING);
		break;
	case DIK_DOWN:
		this->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void RaccoonMario::OnKeyDown(int KeyCode) {
	DebugOut(L"On key down %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		this->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->isOnPlatform) {
			this->SetState(MARIO_STATE_JUMP);
		}
		else {
			if (mario->GetPower() >= 6) {
				mario->isJumping = false;
				SetState(MARIO_STATE_FLY);
				mario->vy = -0.432f;
				mario->startJumpPosition = mario->position.y;
				if (!flyStopwatch->IsRunning()) {
					flyStopwatch->Restart();
				}
				SceneManager::GetInstance()->GetActiveScene()->GetCamera()->SetLimitEdge(Direction::Top, 0.0f);
			}
			else {
				this->SetState(MARIO_STATE_FLOAT);
			}
		}
		break;
	case DIK_0:
		this->SetState(MARIO_STATE_DIE);
		break;
	case DIK_C:
		this->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}


RectBox RaccoonMario::GetBoundingBox() {
	RectBox bounding_box = RectBox(0, 0, 0, 0);
	int height = mario->isSitting ? MARIO_BIG_CROUCH_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT;
	bounding_box.left = mario->position.x - MARIO_BIG_BBOX_WIDTH * 3 / 2;
	bounding_box.top = mario->position.y - height * 3 / 2;
	bounding_box.right = bounding_box.left + MARIO_BIG_BBOX_WIDTH * 3;
	bounding_box.bottom = bounding_box.top + height * 3;
	return bounding_box;
}
