#include "Ground.h"
#include "debug.h"

CGround* CGround::Create(Vec2 position, Vec2 size, bool fullBlock) {
	CGround* ground = new CGround();
	ground->SetPosition(Vec2(position.x, position.y));
	ground->size = size;
	ground->fullBlock = fullBlock;
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
	if (fullBlock) {
		return false;
	}
	if (collisionNy > 0) {
		return true;
	}
	return false;
}


CGround::~CGround()
{
}