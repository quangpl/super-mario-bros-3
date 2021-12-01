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

string CMario::GetAniIdSmall()
{
	bool has_holding = this->holder != NULL;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
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
		if (isSitting)
		{
			ani = "ani-small-mario-idle";
		}
		else
			if (vx == 0)
			{
				ani = "ani-small-mario-idle";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					nx = 1;
					ani = "ani-small-mario-skid";
				}
				else if (vx >= MARIO_RUNNING_SPEED)
					ani = "ani-small-mario-run";
				else
					ani = "ani-small-mario-walk";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}
			else // vx < 0
			{
				if (ax > 0)
				{
					nx = -1;
					ani = "ani-small-mario-skid";
				}
				else if (vx <= -MARIO_RUNNING_SPEED)
					ani = "ani-small-mario-run";
				else
					ani = "ani-small-mario-walk";
				if (has_holding) {
					ani = "ani-small-mario-hold";
				}
			}

	if (ani.compare("ani") == 0) ani = "ani-small-mario-idle";

	return ani;
}


//
// Get animdation ID for big Mario
//
string CMario::GetAniIdBig()
{
	bool has_holding = this->holder != NULL;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			ani = "ani-big-mario-run";
		}
		else if (has_holding) {
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
					ani = "ani-big-mario-hold";
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
				else {
					ani = "ani-big-mario-walk";
				}
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

	if (ani.compare("") == 0) ani = "ani-big-mario-idle";

	return ani;
}

void CMario::Render()
{
	if (state == MARIO_STATE_DIE)
		ani = "ani-small-mario-die";
	else if (level == MARIO_LEVEL_BIG)
		ani = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		ani = GetAniIdSmall();
	// TODO: Need improve with Effect
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2(nx * 1.0f, 1.0f);
	CAnimations::GetInstance()->Get(ani)->Render(position.x, position.y);
	RenderBoundingBox();
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

void CMario::SetLevel(int l)
{
	// TODO : Improve collision framework to remove "hard" behavior to make sure everything right.
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		position.y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
void CMario::OnKeyUp(int KeyCode) {
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

void CMario::OnKeyDown(int KeyCode) {
	DebugOut(L"On key down %d", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		this->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		this->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		this->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		this->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		this->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
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

