#include "Brick.h"

CBrick::CBrick() {
}

CBrick::~CBrick()
{

}

CBrick* CBrick::Create(Vec2 pos, MapData& data)
{
	CBrick* birck = new CBrick();
	birck->SetPosition(Vec2(pos.x, pos.y));
	string rewardItem = data.GetText("HiddenItem", "QuestionCoin");
	birck->state = BRICK_STATE_NORMAL;
	if (rewardItem.compare(ObjectTypeData::RedMushroom.ToString()) == 0) {
		birck->reward = ObjectTypeData::RedMushroom;
	}
	if (rewardItem.compare(ObjectTypeData::QuestionCoin.ToString()) == 0) {
		birck->reward = ObjectTypeData::QuestionCoin;
	}
	return birck;

}


void CBrick::Render()
{
	if (state == BRICK_STATE_HIT) {
		ani = "ani-empty-block";
	}
	else {
		ani = "ani-question-block";
	}
	CAnimations::GetInstance()->Get(ani)->Render(this->position.x, this->position.y);
	//RenderBoundingBox();
}

void CBrick::OnNoCollision(DWORD dt)
{

}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
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

		if (reward == ObjectTypeData::RedMushroom) {
			CMushroom* mushroom = new CMushroom();
			mushroom->SetStartY(this->position.y);
			mushroom->SetPosition(Vec2{ this->position });
			mushroom->SetState(UP_MUSHROOM_STATE_UP);
			SceneManager::GetInstance()->GetActiveScene()->AddObject(mushroom);
		}
		/*
		else if (this->child_item_id == BrickChildItem::Coin) {
			CCoindEffect* coin_effect = new CCoindEffect(x, y);
			int coin_effect_id = effect_manager->Add(coin_effect);
			coin_effect->Start([this, coin_effect_id]() {
				CEffectManager::GetInstance()->Delete(coin_effect_id);
			});
		}*/
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
