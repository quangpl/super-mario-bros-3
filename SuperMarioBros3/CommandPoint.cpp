#include "CommandPoint.h"
#include "debug.h"

CCommandPoint::CCommandPoint()
{

}

void CCommandPoint::Render()
{
	RenderBoundingBox();
}

bool CCommandPoint::CanThrough(CGameObject* sourceObject, float collisionNx, float collisionNy) {
	if (dynamic_cast<CKoopas*>(sourceObject) && sourceObject->GetState() != KOOPAS_STATE_DIE_BY_ATTACK && sourceObject->GetState() != KOOPAS_STATE_DIE_MOVE) {
		return false;
	}
	return true;
}
CCommandPoint* CCommandPoint::Create(Vec2 pos, MapData& data) {
	CCommandPoint* command_point = new CCommandPoint();
	command_point->SetPosition(pos);
	command_point->SetCommand(data.GetText("Command"));
	command_point->size.x = data.GetInt("Width");
	command_point->size.y = data.GetInt("Height");
	return command_point;
}
RectBox CCommandPoint::GetBoundingBox()
{
	this->bounding_box.left = position.x - size.x / 2;
	this->bounding_box.top = position.y - size.y / 2;
	this->bounding_box.right = this->bounding_box.left + size.x;
	this->bounding_box.bottom = this->bounding_box.top + size.y;
	return this->bounding_box;
}

CCommandPoint::~CCommandPoint()
{
}
