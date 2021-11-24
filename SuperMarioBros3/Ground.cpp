#include "Ground.h"
#include "debug.h"

CGround* CGround::Create(Vec2 position, Vec2 size) {
	CGround* ground = new CGround();
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
	l = position.x - BRICK_BBOX_WIDTH / 2;
	t = position.y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH * width;
	b = t + BRICK_BBOX_HEIGHT * height;
}

CGround::~CGround()
{
}