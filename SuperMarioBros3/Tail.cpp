#include "Tail.h"
#include "Stopwatch.h"
#include "Constants.h"
#include "Mario.h"

CTail::CTail(CMario* _owner) {
	this->owner = _owner;
	this->stopwatch = new Stopwatch();
	this->vy = 0;
}

CTail::~CTail()
{
}

void CTail::Attack()
{
	stopwatch->Restart();
	vx = MARIO_TAIL_WIDTH / dt * attackNx;
}
bool CTail::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy) {
	return false;
}
void CTail::Render()
{
	RenderBoundingBox();
}

void CTail::OnNoCollision(DWORD dt)
{

}

void CTail::AttackHandler() {

}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	vx = vx * attackNx;
	if (stopwatch->Elapsed() >= hitTime) {
		this->isDeleted = true;
		return;
	}
	this->dt = dt;

	this->position = this->owner->GetPosition();
	this->SetNx(owner->GetNx() * attackNx);
	RectBox marioBbox = owner->GetBoundingBox();

	this->position.x = (marioBbox.left + marioBbox.right) / 2; // centralize the tail with mario

	if (stopwatch->Elapsed() <= hitTime / 2) {
		attackNx = owner->GetNx();
	}
	else {
		attackNx = -owner->GetNx();
	}

	CCollision::GetInstance()->Process(this, dt, objects);

}

void CTail::SetState(int state)
{

}
RectBox CTail::GetBoundingBox() {
	this->bounding_box.left = position.x + MARIO_TAIL_BBOX_SIZE / 2;
	this->bounding_box.top = position.y + MARIO_TAIL_BBOX_SIZE / 2;
	this->bounding_box.right = this->bounding_box.left + MARIO_TAIL_BBOX_SIZE;
	this->bounding_box.bottom = this->bounding_box.top + MARIO_TAIL_BBOX_SIZE;
	return this->bounding_box;
}
