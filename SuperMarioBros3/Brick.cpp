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

shared_ptr<CBrick> CBrick::Create(Vec2 pos)
{
	shared_ptr<CBrick> brick = make_shared<CBrick>(pos,2,1);
	brick->SetPosition(pos);
	return brick;
}


void CBrick::Render()
{
	/*if (!is_show) {
		return;
	}
	int ani;
	if (this->state == BRICK_STATE_NORMAL) {
		ani = BRICK_ANI_NORMAL;
	}
	else {
		ani = BRICK_ANI_BROKEN;
	}*/
	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
	CAnimation* ani = CAnimations::GetInstance()->Get("ani-empty-block");
	ani->Render(this->position.x, this->position.y);
}

void CBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
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
		is_show = false;
		CEffectManager* effect_manager = CEffectManager::GetInstance();
		CBrickEffect* hit_effect = new CBrickEffect(x, y);
		int hit_effect_id = effect_manager->Add(hit_effect);
		hit_effect->Start([this, hit_effect_id]() {
			is_show = true;
			CEffectManager::GetInstance()->Delete(hit_effect_id);
		});
		if (dynamic_cast<CMushroom*>(this->child_item)) {
			CMushroom* mushroom = dynamic_cast<CMushroom*>(this->child_item);
			mushroom->SetState(UP_MUSHROOM_STATE_UP);
		}
		else if (this->child_item_id == BrickChildItem::Coin) {
			CCoindEffect* coin_effect = new CCoindEffect(x, y);
			int coin_effect_id = effect_manager->Add(coin_effect);
			coin_effect->Start([this, coin_effect_id]() {
				CEffectManager::GetInstance()->Delete(coin_effect_id);
			});
		}
		break;
	}
	default:
		break;
	}
}
RectBox CBrick::GetBoundingBox() {
	this->bounding_box.left = x;
	this->bounding_box.top = y;
	this->bounding_box.right = this->bounding_box.left + BRICK_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + BRICK_BBOX_HEIGHT;
	return this->bounding_box;
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}