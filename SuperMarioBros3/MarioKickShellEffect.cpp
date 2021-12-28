#include "MarioKickShellEffect.h"
#include "MasterMario.h"

CMarioKickShellEffect::CMarioKickShellEffect(Vec2 pos, int _nx) : CEffect(pos.x, pos.y)
{
	this->nx = _nx;
}

void CMarioKickShellEffect::Render()
{
	string ani;
	int marioLevel = CMario::GetInstance()->GetLevel();
	switch (marioLevel)
	{
	case MarioLevel::Big:
		ani = "ani-big-mario-kick";
		break;
	case MarioLevel::Small:
		ani = "ani-small-mario-kick";
		break;
	case MarioLevel::Raccoon:
		ani = "ani-raccoon-mario-kick";
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(ani)->GetTransform()->Scale = Vec2{ this->nx * 1.0f,1.0f };
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CMarioKickShellEffect::Update(DWORD dt)
{
	if (state == MARIO_KICK_SHELL_EFFECT_RUNNING && GetTickCount64() - startTime >= STOP_TIMEOUT) {
		this->callback();
	}
}


void CMarioKickShellEffect::Start(function<void()> _callback)
{
	state = MARIO_KICK_SHELL_EFFECT_RUNNING;
	startTime = GetTickCount64();
	this->callback = _callback;
}
