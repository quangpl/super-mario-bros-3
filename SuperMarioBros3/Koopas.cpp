#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"

CKoopas::CKoopas(int koopas_type, float x, float y)
{
	type = Type::KOOPAS;
	koopas_type = koopas_type;
	this->start_x = x;
	this->start_y = y;
}


void CKoopas::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CKoopas::Render()
{
	//DebugOut(L"ani:%d \n", ani);
	ani = KOOPAS_ANI_WALKING_LEFT;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	bottom = y + KOOPAS_BBOX_HEIGHT;
}
