#include "MarioGrowEffect.h"

CMarioGrowEffect::CMarioGrowEffect(Vec2 pos, int _nx) : CEffect(pos.x, pos.y)
{
	startTime = 0;
	this->nx = _nx;
}

void CMarioGrowEffect::Render()
{
	CAnimations::GetInstance()->Get("ani-mario-grow-up")->GetTransform()->Scale = Vec2{ this->nx * 1.0f,1.0f };
	CAnimations::GetInstance()->Get("ani-mario-grow-up")->Render(x - MARIO_SMALL_BBOX_WIDTH, y - MARIO_SMALL_BBOX_HEIGHT * 3 / 2);
}

void CMarioGrowEffect::Update(DWORD dt)
{
	if (state == MARIO_GROW_UP_EFFECT_RUNNING && GetTickCount64() - startTime >= STOP_TIMEOUT) {
		this->callback();
	}
}


void CMarioGrowEffect::Start(function<void()> _callback)
{
	state = MARIO_GROW_UP_EFFECT_RUNNING;
	startTime = (DWORD)GetTickCount64();
	this->callback = _callback;
}
