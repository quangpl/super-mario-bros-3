#include "Ground.h"
#include "debug.h"

shared_ptr<CGround> CGround::Create(Vec2 position, Vec2 size) {
	shared_ptr<CGround> ground = make_shared<CGround>();
	ground->SetPosition(Vec2(position.x, position.y));
	ground->size = size;
	return ground;
}
CGround::CGround()
{
	type = Type::GROUND;

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