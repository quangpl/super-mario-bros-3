#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (position.x <= move_limitation.left + MARIO_BIG_BBOX_WIDTH / 2) {
		position.x = move_limitation.left + MARIO_BIG_BBOX_WIDTH / 2;
	}
	else if (position.x >= move_limitation.right - MARIO_BIG_BBOX_WIDTH / 2) {
		position.x = move_limitation.right - MARIO_BIG_BBOX_WIDTH / 2;
	}

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

void CMario::OnNoCollision(DWORD dt)
{
	position.x += vx * dt;
	position.y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
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
		OnCollisionWithGoomba(e);
	//else if (dynamic_cast<CCoin*>(e->obj))
	//	OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
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
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
		break;
	}


}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	// TODO: Improve collision framework to do better
	if (level != MARIO_LEVEL_BIG && mushroom->GetEatable()) {
		SetState(MARIO_STATE_TRANSFORM_SMALL_TO_BIG);
		SetLevel(MARIO_LEVEL_BIG);
		mushroom->SetState(UP_MUSHROOM_STATE_DIE);
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
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

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
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
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	bool has_holding = this->holder != NULL;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else if (has_holding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_SHELL_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) {
					aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				}
				else {
					aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				if (has_holding) {
					if (nx > 0) {
						aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_RIGHT;
					}
					else {
						aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_SHELL_LEFT;
					}
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (vx >= MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				if (has_holding) {
					aniId = ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (vx <= -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				if (has_holding) {
					aniId = ID_ANI_MARIO_SMALL_WALK_HOLD_SHELL_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	bool has_holding = this->holder != NULL;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else if (has_holding) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_HOLD_SHELL_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_HOLD_SHELL_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) {
					aniId = ID_ANI_MARIO_IDLE_RIGHT;
				}
				else {
					aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				if (has_holding) {
					if (nx > 0) {
						aniId = ID_ANI_MARIO_IDLE_HOLD_SHELL_RIGHT;
					}
					else {
						aniId = ID_ANI_MARIO_IDLE_HOLD_SHELL_LEFT;
					}
				}

			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (vx >= MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else {
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				if (has_holding) {
					aniId = ID_ANI_MARIO_WALK_HOLD_SHELL_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (vx <= -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_WALKING_LEFT;
				if (has_holding) {
					aniId = ID_ANI_MARIO_WALK_HOLD_SHELL_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	// TODO: Need improve with Effect
	CAnimations::GetInstance()->Get("ani-big-mario-walk")->Render(position.x, position.y);
	//CAnimations* animations = CAnimations::GetInstance();
	//int aniId = -1;
	//if (state == MARIO_STATE_TRANSFORM_SMALL_TO_BIG) {
	//	if (nx > 0) {
	//		aniId = ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_RIGHT;
	//	}
	//	else {
	//		aniId = ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_LEFT;
	//	}
	//	//animations->Get(aniId)->Render(x, y);
	//	//DebugOut(L"Mario ani: %d\n", aniId);
	//	return;
	//}
	//if (state == MARIO_STATE_DIE)
	//	aniId = ID_ANI_MARIO_DIE;
	//else if (level == MARIO_LEVEL_BIG)
	//	aniId = GetAniIdBig();
	//else if (level == MARIO_LEVEL_SMALL)
	//	aniId = GetAniIdSmall();

	////animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	////DebugOut(L"Mario ani: %d \n", aniId);
}

void CMario::SetState(int state)
{
	backup_state = this->state;
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

	case MARIO_STATE_SIT:
		if (holding) {
			return;
		}
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			//y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			//y -= MARIO_SIT_HEIGHT_ADJUST;
		}
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

//void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	/*x = 100;
//	y = 1600;*/
//	//left = x - MARIO_BIG_BBOX_WIDTH / 2;
//	//top = y - MARIO_BIG_BBOX_HEIGHT / 2;
//	//right = left + MARIO_BIG_BBOX_WIDTH;
//	//bottom = top + MARIO_BIG_BBOX_HEIGHT;
//}

void CMario::SetLevel(int l)
{
	// TODO : Improve collision framework to remove "hard" behavior to make sure everything right.
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		//y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
void CMario::OnKeyUp(int KeyCode) {
	DebugOut(L"On key up %d", KeyCode);
}

void CMario::OnKeyDown(int KeyCode) {
	maxVx = MARIO_RUNNING_SPEED;
	ax = MARIO_ACCEL_RUN_X;
	nx = 1;
	DebugOut(L"On key down %d", KeyCode);
}


RectBox CMario::GetBoundingBox() {
	this->bounding_box.left = position.x - MARIO_BIG_BBOX_WIDTH * 3 / 2;
	this->bounding_box.top = position.y - MARIO_BIG_BBOX_HEIGHT * 3 / 2;
	this->bounding_box.right = this->bounding_box.left + MARIO_BIG_BBOX_WIDTH * 3;
	this->bounding_box.bottom = this->bounding_box.top + MARIO_BIG_BBOX_HEIGHT * 3;
	return this->bounding_box;
}

CMario* CMario::__instance = NULL;

CMario* CMario::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CMario();
	}
	return __instance;
}

