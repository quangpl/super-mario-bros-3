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


CGround::~CGround()
{
}