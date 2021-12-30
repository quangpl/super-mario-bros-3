#include "GoombaDieEffect.h"

CGoombaDieEffect::CGoombaDieEffect(Vec2 pos, int _nx) : CEffect(pos.x, pos.y)
{
	this->nx = _nx;
}

void CGoombaDieEffect::Render()
{
	CAnimations::GetInstance()->Get("ani-goomba-die")->GetTransform()->Scale = Vec2{ this->nx * 1.0f,1.0f };
	CAnimations::GetInstance()->Get("ani-goomba-die")->Render(x, y + 10);
}

void CGoombaDieEffect::Update(DWORD dt)
{
	if (state == GOOMBA_DIE_EFFECT_RUNNING && GetTickCount64() - startTime >= STOP_TIMEOUT) {
		this->callback();
	}
}


void CGoombaDieEffect::Start(function<void()> _callback)
{
	state = GOOMBA_DIE_EFFECT_RUNNING;
	startTime = (DWORD)GetTickCount64();
	this->callback = _callback;
}
