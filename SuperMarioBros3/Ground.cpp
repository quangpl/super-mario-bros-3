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
	//CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(702)->Render(x, y);
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x  - BRICK_BBOX_WIDTH /2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH * width;
	b = t + BRICK_BBOX_HEIGHT * height;
}

CGround::~CGround()
{
}