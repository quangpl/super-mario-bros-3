#include "BigMario.h"

void BigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

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
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void BigMario::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
}

void BigMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{

				if (goomba->GetLevel() == GoombaLevel::RedWing) {
					goomba->SetLevel(GoombaLevel::Red);
					goomba->SetState(GOOMBA_STATE_WALKING);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else {
					goomba->SetState(GOOMBA_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
			}
		}
		else // hit by Goomba
		{
			if (untouchable == 0)
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
	else if (dynamic_cast<CMushroom*>(e->obj))
	{
		CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
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
		case KOOPAS_STATE_DIE_BY_ATTACK:
			if (this->holding) {
				this->holder = koopas;
				this->SetState(MARIO_STATE_HOLDING);
				koopas->SetOwner(this);
				return;
			}
			koopas->SetState(KOOPAS_STATE_DIE_MOVE);
			break;
		default:
			if (e->ny < 0) {
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopas->SetState(KOOPAS_STATE_DIE_BY_ATTACK);
			}
			else {
				if (untouchable == 0)
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			break;
		}
	}
}


void BigMario::Render()
{
	bool has_holding = this->holder != NULL;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			ani = "ani-big-mario-high-speed";
		}
		else if (has_holding)
		{
			ani = "ani-big-mario-hold";
		}
		else
		{
			ani = "ani-big-mario-jump";
		}
	}
	else
		if (isSitting)
		{
			ani = "ani-big-mario-crouch";
		}
		else
			if (vx == 0)
			{
				ani = "ani-big-mario-idle";
				if (has_holding) {
					ani = "ani-big-mario-hold-idle";
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					nx = 1;
					ani = "ani-big-mario-skid";
				}
				else if (vx >= MARIO_RUNNING_SPEED)
					ani = "ani-big-mario-run";
				else
					ani = "ani-big-mario-walk";
				if (has_holding) {
					ani = "ani-big-mario-hold";
				}
			}
			else // vx < 0
			{
				if (ax > 0)
				{
					nx = -1;
					ani = "ani-big-mario-skid";
				}
				else if (vx <= -MARIO_RUNNING_SPEED)
					ani = "ani-big-mario-run";
				else
					ani = "ani-big-mario-walk";
				if (has_holding) {
					ani = "ani-big-mario-hold";
				}
			}

	if (ani.compare("ani") == 0) ani = "ani-big-mario-idle";
	// TODO: Need improve with Effect
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2(nx * 1.0f, 1.0f);
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	RenderBoundingBox();
}

void BigMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RELEASE_RUNNING:
		ax = 0;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;
	case MARIO_STATE_IDLE:
		ax = 0;
		if (vx > 0) {
			vx = vx - MARIO_DECREASE_SPEED;
			if (vx < 0)
			{
				vx = 0;
			}
		}
		else if (vx < 0) {
			vx = vx + MARIO_DECREASE_SPEED;
			if (vx > 0)
			{
				vx = 0;
			}
		}
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		if (vx > 0) {
			nx = 1;
		}
		else {
			nx = -1;
		}
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_HOLDING:
		holding = true;
		break;
	case MARIO_STATE_RELEASE_HOLDING:
		holding = false;
		if (this->holder != NULL) {
			if (dynamic_cast<CKoopas*>(this->holder)) {
				CKoopas* koopas = dynamic_cast<CKoopas*>(this->holder);
				koopas->SetOwner(NULL);
				koopas->SetNx(this->nx);
				koopas->SetState(KOOPAS_STATE_DIE_MOVE);
			}
			this->holder = NULL;
		}
		break;
	case MARIO_STATE_TRANSFORM_SMALL_TO_BIG:
		transformation_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	}
	CGameObject::SetState(state);
}

void BigMario::OnKeyUp(int KeyCode) {
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

void BigMario::OnKeyDown(int KeyCode) {
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


RectBox BigMario::GetBoundingBox() {
	this->bounding_box.left = position.x - MARIO_BIG_BBOX_WIDTH * 3 / 2;
	this->bounding_box.top = position.y - MARIO_BIG_BBOX_HEIGHT * 3 / 2;
	this->bounding_box.right = this->bounding_box.left + MARIO_BIG_BBOX_WIDTH * 3;
	this->bounding_box.bottom = this->bounding_box.top + MARIO_BIG_BBOX_HEIGHT * 3;
	return this->bounding_box;
}
