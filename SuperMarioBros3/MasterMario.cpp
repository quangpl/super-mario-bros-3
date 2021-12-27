#include "Game.h"
#include "Collision.h"
#include "MasterMario.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "debug.h"
#include "Mario.h"
#include "SmallMario.h"
#include "BigMario.h"
#include "MarioDamagedEffect.h"


CMasterMario::CMasterMario()
{
	mario = CMario::GetInstance();
}

void CMasterMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->KeyboardHandler();

	//mario->Update(dt, coObjects);
}

void CMasterMario::OnNoCollision(DWORD dt)
{

}
void CMasterMario::KeyboardHandler() {
	LPGAME game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_Z)) {
		mario->SetHolding(true);
	}
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->GetPlayerState()->SetState(MARIO_STATE_RUNNING);
		else
			mario->GetPlayerState()->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->GetPlayerState()->SetState(MARIO_STATE_RUNNING);
		else
			mario->GetPlayerState()->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		mario->GetPlayerState()->SetState(MARIO_STATE_IDLE);
	}
}
void CMasterMario::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CMasterMario::PowerCalculator(DWORD dt) {
	float maxRun = abs(mario->vx) > MARIO_RUNNING_SPEED * 0.85f;

	if (maxRun && mario->isOnPlatform)
		mario->SetPower(max(0.0f, min(mario->GetPower() + PMETER_UP_STEP * dt, PMETER_MAX + 1)));
	else if (mario->GetPower() > 0)
		mario->SetPower(max(0.0f, min(mario->GetPower() - PMETER_DOWN_STEP * dt, PMETER_MAX)));
}
void CMasterMario::Render()
{

}

void CMasterMario::SetState(int state)
{
}


void CMasterMario::OnKeyUp(int KeyCode) {

}
void CMasterMario::OnDamaged() {
	if (mario->GetLevel() == MarioLevel::Small) {
		this->SetState(MARIO_STATE_DIE);
		return;
	}
	else {
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CMarioDamagedEffect* marioDamagedEffect = new CMarioDamagedEffect(mario->position, mario->GetNx());
		int effectId = effectManager->Add(marioDamagedEffect);
		mario->SetDeleted(true);
		marioDamagedEffect->Start([this, effectId]() {
			mario->SetDeleted(false);
			CEffectManager::GetInstance()->Delete(effectId);
			switch (mario->GetLevel())
			{
			case MarioLevel::Big:
				mario->StartUntouchable();
				mario->SetPlayerState(new SmallMario());
				break;
			case MarioLevel::Raccoon:
				mario->StartUntouchable();
				mario->SetPlayerState(new BigMario());
				break;
			default:
				break;
			}
			});
	}
}
void CMasterMario::OnKeyDown(int KeyCode) {
}


RectBox CMasterMario::GetBoundingBox() {
	return RectBox(0, 0, 0, 0);
}
