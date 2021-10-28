#include "MushRoom.h"

CMushroom::CMushroom(int t) {
	this->type = Type::MUSHROOM;
	/*vx = MUSHROOM_SPEED_Y;
	vy = MUSHROOM_SPEED_Y;*/
}
CMushroom::~CMushroom()
{

}

void CMushroom::Render()
{
	CAnimations::GetInstance()->Get(306)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += (MUSHROOM_GRAVITY * dt);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 40;
	top = y - 40;
	right = left + 40;
	bottom = top + 40;
}
