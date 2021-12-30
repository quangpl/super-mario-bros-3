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
#include "MarioKickShellEffect.h"
#include "GreenKoopas.h"
#include "Fireball.h"
#include "Piranha.h"
#include "Venus.h"
#include "ScoreEffect.h"

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
	if (game->IsKeyDown(DIK_A)) {
		mario->SetHolding(true);
	}
	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetNx(1);
		if (game->IsKeyDown(DIK_A))
			mario->GetPlayerState()->SetState(MARIO_STATE_RUNNING);
		else
			mario->GetPlayerState()->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		mario->SetNx(-1);
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
	if (dynamic_cast<Fireball*>(e->obj)) {
		this->OnDamaged();
		e->obj->SetDeleted(true);
	}
	if (dynamic_cast<Piranha*>(e->obj) || dynamic_cast<Venus*>(e->obj)) {
		this->OnDamaged();
	}

}
void CMasterMario::OnKickShell(CGameObject* koopas) {
	CEffectManager* effectManager = CEffectManager::GetInstance();
	CMarioKickShellEffect* marioKickShellEffect = new CMarioKickShellEffect(mario->position, mario->GetNx());
	int effectId = effectManager->Add(marioKickShellEffect);
	mario->SetDeleted(true);
	marioKickShellEffect->Start([this, effectId, koopas]() {
		mario->SetDeleted(false);
		CEffectManager::GetInstance()->Delete(effectId);
		koopas->SetNx(mario->GetNx());
		koopas->SetState(KOOPAS_STATE_DIE_MOVE);
		});
}
void CMasterMario::OnReleaseHolding() {
	mario->holding = false;
	if (mario->holder != NULL) {
		if (dynamic_cast<CKoopas*>(mario->holder)) {
			CEffectManager* effectManager = CEffectManager::GetInstance();
			CMarioKickShellEffect* marioKickShellEffect = new CMarioKickShellEffect(mario->position, mario->GetNx());
			int effectId = effectManager->Add(marioKickShellEffect);
			mario->SetDeleted(true);
			marioKickShellEffect->Start([this, effectId]() {
				mario->SetDeleted(false);
				CEffectManager::GetInstance()->Delete(effectId);
				CKoopas* koopas = dynamic_cast<CKoopas*>(mario->holder);
				koopas->SetOwner(NULL);
				koopas->SetNx(mario->GetNx());
				koopas->SetState(KOOPAS_STATE_DIE_MOVE);
				mario->holder = NULL;
				});
		}
		if (dynamic_cast<GreenKoopas*>(mario->holder)) {
			CEffectManager* effectManager = CEffectManager::GetInstance();
			CMarioKickShellEffect* marioKickShellEffect = new CMarioKickShellEffect(mario->position, mario->GetNx());
			int effectId = effectManager->Add(marioKickShellEffect);
			mario->SetDeleted(true);
			marioKickShellEffect->Start([this, effectId]() {
				mario->SetDeleted(false);
				CEffectManager::GetInstance()->Delete(effectId);
				GreenKoopas* koopas = dynamic_cast<GreenKoopas*>(mario->holder);
				koopas->SetOwner(NULL);
				koopas->SetNx(mario->GetNx());
				koopas->SetState(KOOPAS_STATE_DIE_MOVE);
				mario->holder = NULL;
				});
		}
	}
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
void CMasterMario::OnHitEnermy(CGameObject* obj) {
	if (GetTickCount64() - mario->lastTimeHit <= 1000) {
		mario->scoreLevel = mario->scoreLevel + 1;
	}
	else {
		mario->scoreLevel = 0;
	}
	mario->lastTimeHit = GetTickCount64();
	ScoreNum scoreNum = ScoreNum::SCORE100;

	switch (mario->scoreLevel)
	{
	case 0:
		scoreNum = ScoreNum::SCORE100;
		break;
	case 1:
		scoreNum = ScoreNum::SCORE200;
		break;
	case 2:
		scoreNum = ScoreNum::SCORE400;
		break;
	case 3:
		scoreNum = ScoreNum::SCORE800;
		break;
	case 4:
		scoreNum = ScoreNum::SCORE1000;
		break;
	case 5:
		scoreNum = ScoreNum::SCORE2000;
		break;
	case 6:
		scoreNum = ScoreNum::SCORE4000;
		break;
	case 7:
		scoreNum = ScoreNum::SCORE8000;
		break;
	default:
		break;
	}

	CEffectManager* effectManager = CEffectManager::GetInstance();
	ScoreEffect* scoreEffect = new ScoreEffect(obj->position.x, obj->position.y - 48 * 2, scoreNum);
	int effectId = effectManager->Add(scoreEffect);

	scoreEffect->Start([this, effectId]() {
		CEffectManager::GetInstance()->Delete(effectId);
		});

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
