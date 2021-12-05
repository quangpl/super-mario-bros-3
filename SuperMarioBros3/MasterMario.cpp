#include "Game.h"
#include "Collision.h"
#include "MasterMario.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "debug.h"
#include "Mario.h"

CMasterMario::CMasterMario() : CGameObject()
{
	mario = CMario::GetInstance();
}

void CMasterMario::SetHolder(LPGAMEOBJECT _holder) { this->holder = _holder; }
LPGAMEOBJECT CMasterMario::GetHolder() { return this->holder; }

void CMasterMario::SetHolding(bool _holding) { this->holding = _holding; }
bool CMasterMario::GetHolding() { return this->holding; }

void CMasterMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	mario->Update(dt, coObjects);
}

void CMasterMario::OnNoCollision(DWORD dt)
{

}

void CMasterMario::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CMasterMario::Render()
{
	RenderBoundingBox();
}

void CMasterMario::SetState(int state)
{
	CGameObject::SetState(state);
}


void CMasterMario::OnKeyUp(int KeyCode) {

}

void CMasterMario::OnKeyDown(int KeyCode) {
}


RectBox CMasterMario::GetBoundingBox() {
	this->bounding_box.left = this->position.x - this->size.x / 2;
	this->bounding_box.top = this->position.y - this->size.y / 2;
	this->bounding_box.right = this->bounding_box.left + this->size.x;
	this->bounding_box.bottom = this->bounding_box.top + this->size.y;
	return this->bounding_box;
}
