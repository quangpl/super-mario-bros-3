#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->playerState->Update(dt, coObjects);
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

