#include "Mario.h"
#include "MasterMario.h"
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "debug.h"
#include "Collision.h"
#include "SmallMario.h"
#include "BigMario.h"


void CMario::StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
void CMario::SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
LPGAMEOBJECT  CMario::GetHolder() { return this->holder; }

void  CMario::SetHolding(bool _holding) { this->holding = _holding; }
bool  CMario::GetHolding() { return this->holding; }

void CMario::SetPlayerState(CMasterMario* pState) {
	// small to big
	if (dynamic_cast<SmallMario*>(this->playerState) && dynamic_cast<BigMario*>(pState)) {
		this->position.y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) * 3 / 2;
	}
	this->playerState = pState;
}

CMasterMario* CMario::GetPlayerState() {
	return this->playerState;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->playerState->Update(dt, coObjects);
}

int CMario::IsCollidable()
{
	return (state != MARIO_STATE_DIE);
}

int CMario::IsBlocking()
{
	return (state != MARIO_STATE_DIE && untouchable == 0);
}
void CMario::OnNoCollision(DWORD dt)
{
	this->playerState->OnNoCollision(dt);
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	this->playerState->OnCollisionWith(e);
}

void CMario::Render()
{
	this->playerState->Render();
	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
}

bool CMario::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return false;
}
void CMario::OnKeyUp(int KeyCode) {
	if (this->playerState != NULL) {
		this->playerState->OnKeyUp(KeyCode);
	}
}

void CMario::OnKeyDown(int KeyCode) {
	DebugOut(L"On key down %d", KeyCode);
	if (this->playerState != NULL) {
		this->playerState->OnKeyDown(KeyCode);
	}
}


RectBox CMario::GetBoundingBox() {
	return this->playerState->GetBoundingBox();
}

CMario* CMario::__instance = NULL;

CMario* CMario::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CMario();
	}
	return __instance;
}

