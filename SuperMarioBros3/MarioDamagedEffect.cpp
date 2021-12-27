#include "MarioDamagedEffect.h"

CMarioDamagedEffect::CMarioDamagedEffect(Vec2 pos, int _nx) : CEffect(pos.x, pos.y)
{
	this->nx = _nx;
}

void CMarioDamagedEffect::Render()
{
	CAnimations::GetInstance()->Get("ani-mario-damaged")->GetTransform()->Scale = Vec2{ this->nx * 1.0f,1.0f };
	CAnimations::GetInstance()->Get("ani-mario-damaged")->Render(x - MARIO_SMALL_BBOX_WIDTH, y - MARIO_SMALL_BBOX_HEIGHT * 3 / 2);
}

void CMarioDamagedEffect::Update(DWORD dt)
{
	if (state == MARIO_DAMAGED_EFFECT_RUNNING && GetTickCount64() - startTime >= STOP_TIMEOUT) {
		this->callback();
	}
}


void CMarioDamagedEffect::Start(function<void()> _callback)
{
	state = MARIO_DAMAGED_EFFECT_RUNNING;
	startTime = GetTickCount64();
	this->callback = _callback;
}
