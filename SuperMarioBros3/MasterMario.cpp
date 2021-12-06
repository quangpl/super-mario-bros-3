#include "Game.h"
#include "Collision.h"
#include "MasterMario.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "debug.h"
#include "Mario.h"

CMasterMario::CMasterMario()
{
	mario = CMario::GetInstance();
}

void CMasterMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//mario->Update(dt, coObjects);
}

void CMasterMario::OnNoCollision(DWORD dt)
{

}

void CMasterMario::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CMasterMario::Render()
{

}

void CMasterMario::SetState(int state)
{
}


void CMasterMario::OnKeyUp(int KeyCode) {

}

void CMasterMario::OnKeyDown(int KeyCode) {
}


RectBox CMasterMario::GetBoundingBox() {
	return RectBox(0, 0, 0, 0);
}
