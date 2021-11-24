#include "ActivationPoint.h"
#include "debug.h"

CActivationPoint::CActivationPoint(int w, int h, int command)
{
	type = Type::ActivationPoint;
	this->width = w;
	this->height = h;
	this->command = command;
}

void CActivationPoint::Render()
{
	//RenderBoundingBox();
}

bool CActivationPoint::CanThrough(CGameObject* sourceObject, float collisionNx, float collisionNy) {
	if (dynamic_cast<CKoopas*>(sourceObject) && sourceObject->GetState() != KOOPAS_STATE_DIE_BY_ATTACK && sourceObject->GetState() != KOOPAS_STATE_DIE_MOVE) {
		return false;
	}
	return true;
}

void CActivationPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x - ACTIVATION_POINT_WIDTH / 2;
	t = y - ACTIVATION_POINT_HEIGHT / 2;
	r = l + ACTIVATION_POINT_WIDTH * width;
	b = t + ACTIVATION_POINT_HEIGHT * height;*/
}

CActivationPoint::~CActivationPoint()
{
}