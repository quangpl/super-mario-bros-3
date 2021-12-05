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


void CMario::StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
void CMario::SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
LPGAMEOBJECT  CMario::GetHolder() { return this->holder; }

void  CMario::SetHolding(bool _holding) { this->holding = _holding; }
bool  CMario::GetHolding() { return this->holding; }

void CMario::SetPlayerState(CMasterMario* pState) {
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
	return this->playerState->IsCollidable();
}

int CMario::IsBlocking() {
	return this->playerState->IsBlocking();
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

