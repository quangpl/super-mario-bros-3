#include "Coin.h"
#include "Tail.h"
#include "Mario.h"
CCoin::CCoin() {
	switchStopWatch = new Stopwatch();
}

CCoin::~CCoin()
{

}

CCoin* CCoin::Create(Vec2 pos, int state)
{
	CCoin* coin = new CCoin();
	coin->backupPos = pos;
	coin->SetPosition(Vec2(pos.x, pos.y));
	coin->state = state;
	return coin;

}
void CCoin::Switch() {
	backupState = state;
	if (state == COIN_STATE_NORMAL_COIN) {
		SetState(COIN_STATE_BRICK);
	}
	else {
		SetState(COIN_STATE_NORMAL_COIN);
	}
	isSwitching = true;
	switchStopWatch->Restart();
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
	if (isSwitching && switchStopWatch->Elapsed() >= REVERT_TIMEOUT) {
		SetState(backupState);
		switchStopWatch->Stop();
		isSwitching = false;
	}
	position = backupPos;
	CGameObject::Update(dt, objects);
	CCollision::GetInstance()->Process(this, dt, objects);
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
}

int CCoin::IsCollidable() {
	return 1;
}

void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (this->isDeleted == false && dynamic_cast<CTail*>(e->obj)) {
		CEffectManager::GetInstance()->Add(new BrokenBrickEffect(position));
		this->isDeleted = true;
	}
	if (state == COIN_STATE_NORMAL_COIN && this->isDeleted == false && dynamic_cast<CMario*>(e->obj)) {
		this->isDeleted = true;
	}
}
RectBox CCoin::GetBoundingBox() {
	this->bounding_box.left = position.x;
	this->bounding_box.top = position.y;
	this->bounding_box.right = this->bounding_box.left + COIN_BBOX_WIDTH;
	this->bounding_box.bottom = this->bounding_box.top + COIN_BBOX_HEIGHT;
	return this->bounding_box;
}