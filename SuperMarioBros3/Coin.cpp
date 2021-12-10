#include "Coin.h"

CCoin::CCoin() {
}

CCoin::~CCoin()
{

}

CCoin* CCoin::Create(Vec2 pos, int state)
{
	CCoin* coin = new CCoin();
	coin->SetPosition(Vec2(pos.x, pos.y));
	coin->state = state;
	return coin;

}


void CCoin::Render()
{
	if (state == COIN_STATE_NORMAL_COIN) {
		ani = "ani-coin";
	}
	else if (state == COIN_STATE_BRICK) {
		ani = "ani-brick";

	}
	CAnimations::GetInstance()->Get(ani)->Render(this->position.x + COIN_BBOX_WIDTH / 2, this->position.y + COIN_BBOX_HEIGHT / 2);
	RenderBoundingBox();
}

void CCoin::OnNoCollision(DWORD dt)
{

}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void CCoin::SetState(int state)
{

}
RectBox CCoin::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + COIN_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + COIN_BBOX_HEIGHT;
	return this->bounding_box;
}
