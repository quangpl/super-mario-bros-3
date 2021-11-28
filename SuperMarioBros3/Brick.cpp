#include "Brick.h"

CBrick::CBrick(Vec2 _position, int _brickType, int _child_item_id)
{
	this->position = _position;
	this->brickType = _brickType;
	this->type = Type::BRICK;
	this->vx = 0;
	this->vy = 0;
	this->child_item_id = _child_item_id;
	if (brickType == BrickType::Question) {
		state = BRICK_STATE_NORMAL;
	}
	else {
		state = BRICK_ANI_BROKEN;
	}
}

CBrick::~CBrick()
{

}

CBrick* CBrick::Create(Vec2 pos, Vec2 size)
{
	CBrick* brick = new CBrick(pos, 2, 1);
	brick->SetPosition(pos);
	brick->size = size;
	return brick;
}


void CBrick::Render()
{
	CAnimation* ani = CAnimations::GetInstance()->Get("ani-empty-block");
	ani->Render(this->position.x + BRICK_BBOX_WIDTH / 2, this->position.y + BRICK_BBOX_HEIGHT / 2);
	RenderBoundingBox();
}

void CBrick::OnNoCollision(DWORD dt)
{
	/*x += vx * dt;
	y += vy * dt;*/
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
		//is_show = false;
		//CEffectManager* effect_manager = CEffectManager::GetInstance();
		////CBrickEffect* hit_effect = new CBrickEffect(x, y);
		//int hit_effect_id = effect_manager->Add(hit_effect);
		//hit_effect->Start([this, hit_effect_id]() {
		//	is_show = true;
		//	CEffectManager::GetInstance()->Delete(hit_effect_id);
		//});
		//if (dynamic_cast<CMushroom*>(this->child_item)) {
		//	CMushroom* mushroom = dynamic_cast<CMushroom*>(this->child_item);
		//	mushroom->SetState(UP_MUSHROOM_STATE_UP);
		//}
		//else if (this->child_item_id == BrickChildItem::Coin) {
		//	CCoindEffect* coin_effect = new CCoindEffect(x, y);
		//	int coin_effect_id = effect_manager->Add(coin_effect);
		//	coin_effect->Start([this, coin_effect_id]() {
		//		CEffectManager::GetInstance()->Delete(coin_effect_id);
		//	});
		//}
		//break;
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
