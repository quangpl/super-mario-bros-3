#include "Ground.h"
#include "debug.h"

CGround::CGround(int w, int h, bool i)
{
	type = Type::GROUND;
	this->width = w;
	this->height = h;
	this->interact = i;

}

void CGround::Render()
{
	RenderBoundingBox();
}
bool CGround::CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy) {
	if (collisionNy > 0) {
		return true;
	}
	return false;
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH * width;
	b = t + BRICK_BBOX_HEIGHT * height;
}

CGround::~CGround()
{
}