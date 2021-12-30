#include "Brick.h"
#include "Mario.h"
#include "Tail.h"
#include "BrokenBrickEffect.h"
#include "GreenMushroom.h"
#include "ScoreEffect.h"

CBrick::CBrick() {
	this->brickType = BrickType::QuestionBrick;
}

CBrick::~CBrick()
{

}

CBrick* CBrick::Create(Vec2 pos, MapData& data)
{
	CBrick* birck = new CBrick();
	birck->backupPos = pos;
	birck->SetPosition(Vec2(pos.x, pos.y));
	string rewardItem = data.GetText("HiddenItem", "QuestionCoin");
	birck->brickType = data.GetBool("AsBrick", false) ? BrickType::DiamondBrick : BrickType::QuestionBrick;
	birck->state = BRICK_STATE_NORMAL;
	if (rewardItem.compare(ObjectTypeData::RedMushroom.ToString()) == 0) {
		birck->reward = ObjectTypeData::RedMushroom;
	}
	if (rewardItem.compare(ObjectTypeData::QuestionCoin.ToString()) == 0) {
		birck->reward = ObjectTypeData::QuestionCoin;
	}
	if (rewardItem.compare(ObjectTypeData::GreenMushroom.ToString()) == 0) {
		birck->reward = ObjectTypeData::GreenMushroom;
	}
	if (rewardItem.compare(ObjectTypeData::RaccoonLeaf.ToString()) == 0) {
		birck->reward = ObjectTypeData::RaccoonLeaf;
	}
	if (rewardItem.compare(ObjectTypeData::PSwitch.ToString()) == 0) {
		birck->reward = ObjectTypeData::PSwitch;
	}
	return birck;

}


void CBrick::Render()
{
	ani = brickType == BrickType::QuestionBrick ? "ani-question-block" : "ani-brick-time-freeze";

	if (state == BRICK_STATE_HIT || state == BRICK_STATE_BROKEN) {
		ani = "ani-empty-block";
	}
	if (ani.compare("") == 0) {
		return;
	}
	CAnimations::GetInstance()->Get(ani)->Render(this->position.x + BRICK_BBOX_WIDTH / 2, this->position.y + BRICK_BBOX_HEIGHT / 2);
	RenderBoundingBox();
}

void CBrick::OnNoCollision(DWORD dt)
{

}
void CBrick::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CTail*>(e->obj) && this->GetState() != BRICK_STATE_HIT) {
		this->SetState(BRICK_STATE_HIT);
		if (brickType == BrickType::DiamondBrick) {
			CEffectManager::GetInstance()->Add(new BrokenBrickEffect(position));
		}
	}
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	this->position = backupPos;
	CCollision::GetInstance()->Process(this, dt, objects);
}
void CBrick::GenerateRewardByMarioLevel() {
	int marioLevel = CMario::GetInstance()->GetLevel();
	switch (marioLevel)
	{
	case MarioLevel::Small:
	{
		CRedMushroom* mushroom = new CRedMushroom();
		mushroom->SetStartY(this->position.y + BRICK_BBOX_HEIGHT / 2);
		mushroom->SetPosition(Vec2{ this->position.x + BRICK_BBOX_WIDTH / 2,this->position.y + BRICK_BBOX_HEIGHT / 2 });
		mushroom->SetState(UP_MUSHROOM_STATE_UP);
		SceneManager::GetInstance()->GetActiveScene()->AddObject(mushroom);
		break;
	}
	case MarioLevel::Big:
	{
		MarioLeaf* leaf = new MarioLeaf(position + Vec2(2, 0));
		SceneManager::GetInstance()->GetActiveScene()->AddObject(leaf);
		break;
	}
	default:
		// For Raccoon temporary
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CCoindEffect* coinEffect = new CCoindEffect(this->position.x, this->position.y);
		int coinEffectId = effectManager->Add(coinEffect);
		coinEffect->Start([this, coinEffectId]() {
			CEffectManager::GetInstance()->Delete(coinEffectId);
			});
		break;
	}
}
void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case BRICK_STATE_BROKEN:
		// need implement
	case BRICK_STATE_HIT:
	{
		isDeleted = true;
		CEffectManager* effectManager = CEffectManager::GetInstance();
		CBrickEffect* hitBrickEffect = new CBrickEffect(position.x, position.y);
		int effectId = effectManager->Add(hitBrickEffect);
		hitBrickEffect->Start([this, effectId]() {
			isDeleted = false;
			CEffectManager::GetInstance()->Delete(effectId);
			});

		if (reward == ObjectTypeData::QuestionCoin) {
			CCoindEffect* coinEffect = new CCoindEffect(this->position.x, this->position.y);
			int coinEffectId = effectManager->Add(coinEffect);
			coinEffect->Start([this, coinEffectId, effectManager]() {
				CEffectManager::GetInstance()->Delete(coinEffectId);
				ScoreEffect* scoreEffect = new ScoreEffect(this->position.x, this->position.y - 48, ScoreNum::SCORE100);
				int effectId = effectManager->Add(scoreEffect);
				scoreEffect->Start([this, effectId]() {
					CEffectManager::GetInstance()->Delete(effectId);
					});
				});
		}
		else if (reward == ObjectTypeData::PSwitch) {
			PSwitch* pSwitch = new PSwitch(position);
			SceneManager::GetInstance()->GetActiveScene()->AddObject(pSwitch);
		}
		else if (reward == ObjectTypeData::GreenMushroom) {
			GreenMushroom* mushroom = new GreenMushroom();
			mushroom->SetStartY(this->position.y + BRICK_BBOX_HEIGHT / 2);
			mushroom->SetPosition(Vec2{ this->position.x + BRICK_BBOX_WIDTH / 2,this->position.y + BRICK_BBOX_HEIGHT / 2 });
			mushroom->SetState(UP_MUSHROOM_STATE_UP);
			SceneManager::GetInstance()->GetActiveScene()->AddObject(mushroom);
		}
		else if (reward == ObjectTypeData::RaccoonLeaf || reward == ObjectTypeData::RedMushroom) {
			GenerateRewardByMarioLevel();
		}
		break;
	}
	default:
		break;
	}

}

RectBox CBrick::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + BRICK_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + BRICK_BBOX_HEIGHT;
	return this->bounding_box;
}

int CBrick::IsCollidable() {
	return 1;
}

bool CBrick::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return false;
}