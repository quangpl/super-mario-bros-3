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
#include "MarioGrowEffect.h"
#include "PSwitch.h"
#include "RaccoonMario.h"

void CMario::StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
void CMario::SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
LPGAMEOBJECT  CMario::GetHolder() { return this->holder; }

void  CMario::SetHolding(bool _holding) { this->holding = _holding; }
bool  CMario::GetHolding() { return this->holding; }

void  CMario::SetLevel(int _level) { this->level = _level; }
int  CMario::GetLevel() { return this->level; }



void  CMario::SetPower(float p) { this->power = p; }
float  CMario::GetPower() { return this->power; }


void CMario::SetPlayerState(CMasterMario* pState) {
	this->isAttacking = false;
	if(dynamic_cast<RaccoonMario*>(this->playerState)){
		RaccoonMario* racoon = dynamic_cast<RaccoonMario*>(this->playerState);
		if (racoon->tail) {
			racoon->tail->SetActive(false);
			racoon->tail = NULL;
		}
	}
	if (dynamic_cast<SmallMario*>(this->playerState) && dynamic_cast<BigMario*>(pState) || dynamic_cast<BigMario*>(this->playerState) && dynamic_cast<RaccoonMario*>(pState)) {
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CMarioGrowEffect* marioGrowEffect = new CMarioGrowEffect(position, this->nx);
		int effectId = effectManager->Add(marioGrowEffect);
		isActive = false;
		marioGrowEffect->Start([this, effectId]() {
			isActive = true;
			CEffectManager::GetInstance()->Delete(effectId);
			});
		this->position.y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) * 3 / 2;
	}
	this->playerState = pState;
}

CMasterMario* CMario::GetPlayerState() {
	return this->playerState;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Limit moving area
	RectBox currentStateBBox = playerState->GetBoundingBox();
	float stateWidth = currentStateBBox.right - currentStateBBox.left;
	float stateHeight = currentStateBBox.top - currentStateBBox.bottom;

	if (position.x <= moveLimitaion.left + stateWidth / 2) {
		position.x = moveLimitaion.left + stateWidth / 2;
	}

	else if (position.x >= moveLimitaion.right - stateWidth / 2) {
		position.x = moveLimitaion.right - stateWidth / 2;
	}

	if (!isActive) {
		return;
	}
	this->playerState->Update(dt, coObjects);
	
}

int CMario::IsCollidable()
{
	return (state != MARIO_STATE_DIE);
}

void CMario::OnNoCollision(DWORD dt)
{
	isOnPlatform = false;
	this->playerState->OnNoCollision(dt);
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<PSwitch*>(e->obj) && e->ny < 0) {
		e->obj->SetState(PSWITCH_STATE_PRESSED);
	}
	this->playerState->OnCollisionWith(e);
	if (e->ny < 0) {
		isOnPlatform = true;
		isJumping = false;
	}
}

void CMario::OnBlockingOnY(int jetY)
{

	
}

void CMario::OnBlockingOnX(int jetX)
{
}

void CMario::Render()
{
	this->playerState->Render();
	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
}

bool CMario::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return untouchable == 1 ? true : false;
}
void CMario::OnKeyUp(int KeyCode) {
	if (!CGame::GetInstance()->IsEnableKeyBoard()) {
		return;
	}
	if (this->playerState != NULL) {
		this->playerState->OnKeyUp(KeyCode);
	}
}

void CMario::OnKeyDown(int KeyCode) {
	if (!CGame::GetInstance()->IsEnableKeyBoard()) {
		return;
	}
	DebugOut(L"On key down %d", KeyCode);
	if (this->playerState != NULL) {
		this->playerState->OnKeyDown(KeyCode);
	}
}


RectBox CMario::GetBoundingBox() {
	this->bounding_box = this->playerState->GetBoundingBox();
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

