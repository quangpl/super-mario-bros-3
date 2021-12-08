#include "SmallMario.h"
#include "BigMario.h"

SmallMario::SmallMario() : CMasterMario()
{

}

void SmallMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	mario->SetVelocityX(mario->GetSpeed().x + mario->ax * dt);
	mario->SetVelocityY(mario->GetSpeed().y + mario->ay * dt);


	/*if (position.x <= move_limitation.left + MARIO_BIG_BBOX_WIDTH / 2) {
		position.x = move_limitation.left + MARIO_BIG_BBOX_WIDTH / 2;
	}
	else if (position.x >= move_limitation.right - MARIO_BIG_BBOX_WIDTH / 2) {
		position.x = move_limitation.right - MARIO_BIG_BBOX_WIDTH / 2;
	}*/
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT)) {
		this->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		this->SetState(MARIO_STATE_WALKING_LEFT);
	}
	//DebugOut(L"Mario vx: %f \n", vx);
	if (abs(mario->GetSpeed().x) > abs(mario->maxVx)) {
		mario->SetVelocityX(mario->maxVx);
	};

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - mario->untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		mario->untouchable_start = 0;
		mario->untouchable = 0;
	}

	mario->isOnPlatform = false;

	CCollision::GetInstance()->Process(mario, dt, coObjects);
}

void SmallMario::OnNoCollision(DWORD dt)
{
	mario->position.x += mario->GetSpeed().x * dt;
	mario->position.y += mario->GetSpeed().y * dt;
}

void SmallMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		mario->vy = 0;
		if (e->ny < 0) mario->isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
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
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
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
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
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
			/*if (dynamic_cast<CCoin*>(e->obj)) {
				coin++;
			}*/
			brick->SetState(BRICK_STATE_HIT);
		}
	}
	else if (dynamic_cast<CRedMushroom*>(e->obj))
	{
		CRedMushroom* mushroom = dynamic_cast<CRedMushroom*>(e->obj);
		// TODO: Improve collision framework to do better
		if (mushroom->GetEatable()) {
			mario->SetPlayerState(new BigMario());
			mushroom->SetState(UP_MUSHROOM_STATE_DIE);
		}
	}
	else if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		switch (koopas->GetState())
		{
			// TODO: Improve collision framework to make it easier
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
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			break;
		}
	}
}


void SmallMario::Render()
{
	if (mario->GetState() == MARIO_STATE_DIE)
	{
		ani = "ani-small-mario-die";
		CAnimations::GetInstance()->Get(ani)->Render(mario->position.x, mario->position.y);
		return;
	}
	bool has_holding = mario->holder != NULL;
	if (!mario->isOnPlatform)
	{
		if (abs(mario->ax) == MARIO_ACCEL_RUN_X)
		{
			ani = "ani-small-mario-high-jump";
		}
		else if (has_holding)
		{
			ani = "ani-small-mario-hold";
		}
		else
		{
			ani = "ani-small-mario-jump";
		}
	}
	else
		if (mario->isSitting)
		{
			ani = "ani-small-mario-idle";
		}
		else
			if (mario->vx == 0)
			{
				ani = "ani-small-mario-idle";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}
			else if (mario->vx > 0)
			{
				if (mario->ax < 0)
				{
					mario->SetNx(1);
					ani = "ani-small-mario-skid";
				}
				else if (mario->GetSpeed().x >= MARIO_RUNNING_SPEED)
					ani = "ani-small-mario-run";
				else
					ani = "ani-small-mario-walk";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}
			else // vx < 0
			{
				if (mario->ax > 0)
				{
					mario->SetNx(-1);
					ani = "ani-small-mario-skid";
				}
				else if (mario->GetSpeed().x <= -MARIO_RUNNING_SPEED)
					ani = "ani-small-mario-run";
				else
					ani = "ani-small-mario-walk";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}

	if (ani.compare("ani") == 0) ani = "ani-small-mario-idle";
	// TODO: Need improve with Effect
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2{ mario->GetNx() * 1.0f, 1.0f };
	CAnimations::GetInstance()->Get(ani)->Render(mario->position.x, mario->position.y);
	mario->RenderBoundingBox();
}

void SmallMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RELEASE_RUNNING:
		mario->ax = 0;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (mario->isSitting) break;
		mario->maxVx = MARIO_RUNNING_SPEED;
		mario->ax = MARIO_ACCEL_RUN_X;
		mario->SetNx(1);
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (mario->isSitting) break;
		mario->maxVx = -MARIO_RUNNING_SPEED;
		mario->ax = -MARIO_ACCEL_RUN_X;
		mario->SetNx(-1);
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
	}
	mario->SetState(state);
}

void SmallMario::OnKeyUp(int KeyCode) {
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

void SmallMario::OnKeyDown(int KeyCode) {
	DebugOut(L"On key down %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		this->SetState(MARIO_STATE_SIT);
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


RectBox SmallMario::GetBoundingBox() {
	RectBox bounding_box = RectBox(0, 0, 0, 0);
	bounding_box.left = mario->position.x - MARIO_SMALL_BBOX_WIDTH * 3 / 2;
	bounding_box.top = mario->position.y - MARIO_SMALL_BBOX_HEIGHT * 3 / 2;
	bounding_box.right = bounding_box.left + MARIO_SMALL_BBOX_WIDTH * 3;
	bounding_box.bottom = bounding_box.top + MARIO_SMALL_BBOX_HEIGHT * 3;
	return bounding_box;
}
