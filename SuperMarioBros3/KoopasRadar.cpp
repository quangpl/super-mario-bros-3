#include "KoopasRadar.h"
#include "Ground.h"
#include "Coin.h"

CKoopasRadar::CKoopasRadar(CKoopas* _owner) :CGameObject()
{
	this->owner = _owner;
}

RectBox CKoopasRadar::GetBoundingBox() {
	bounding_box.left = position.x - KOOPAS_RADAR_SIZE / 2;
	bounding_box.top = position.y - KOOPAS_RADAR_SIZE / 2;
	bounding_box.right = bounding_box.left + KOOPAS_RADAR_SIZE;
	bounding_box.bottom = bounding_box.top + KOOPAS_RADAR_SIZE;
	return this->bounding_box;
}

void CKoopasRadar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->owner->GetState() != KOOPAS_STATE_WALKING) {
		this->SetDeleted(true);
		return;
	}
	int ownerNx = this->owner->vx > 0 ? 1 : -1;
	RectBox ownerBbox = this->owner->GetBoundingBox();
	float ownerWidth = ownerBbox.right - ownerBbox.left;
	float ownerHeight = ownerBbox.bottom - ownerBbox.top;
	if (ownerNx > 0) {
		this->position.x = this->owner->position.x + ownerWidth / 2 + KOOPAS_RADAR_SIZE / 2 + KOOPAS_RADAR_OWNER_DISTANCE;
	}
	else {
		this->position.x = this->owner->position.x - ownerWidth / 2 - KOOPAS_RADAR_SIZE / 2 + KOOPAS_RADAR_OWNER_DISTANCE;
	}
	bool turnBack = true;
	this->position.y = this->owner->position.y + ownerHeight / 2 + KOOPAS_RADAR_SIZE / 2 + KOOPAS_RADAR_OWNER_DISTANCE;
	for (LPGAMEOBJECT obj : *coObjects) {
		RectBox objBbox = obj->GetBoundingBox();
		if (dynamic_cast<CKoopasRadar*>(obj)) {
			continue;
		}
		if (CCollision::GetInstance()->CheckAABB(objBbox, this->GetBoundingBox())) {
			if (dynamic_cast<CGround*>(obj) || dynamic_cast<CCoin*>(obj)) {
				turnBack = false;
			}
		}
	}

	if (turnBack) {
		DebugOut(L"No Overlapp \n");
		this->owner->vx = -this->owner->vx;
		this->owner->SetNx(-this->owner->GetNx());
	}
}

void CKoopasRadar::Render()
{
	RenderBoundingBox();
}


bool CKoopasRadar::CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy)
{
	return true;
}