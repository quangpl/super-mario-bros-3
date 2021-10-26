#include "Brick.h"

CBrick::CBrick(float x, float y, int brickType)
{
	this->brickType = brickType;
	this->type = Type::BRICK;
	this->x = x;
	this->y = y;
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

void CBrick::Render()
{
	int ani;
	if (this->state == BRICK_STATE_NORMAL) {
		ani = BRICK_ANI_NORMAL;
	}
	else {
		ani = BRICK_ANI_BROKEN;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x,y);
	//RenderBoundingBox();

}

void CBrick::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
}


void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}