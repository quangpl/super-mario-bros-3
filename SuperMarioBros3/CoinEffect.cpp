#include "CoinEffect.h"

CCoindEffect::CCoindEffect(float _x, float _y) : CEffect(_x, _y)
{
	this->start_y = _y;
}

void CCoindEffect::Render()
{
	CAnimations::GetInstance()->Get("ani-coin-obtained")->Render(x + COIN_BBOX_SIZE / 2, y + COIN_BBOX_SIZE / 2);
}

void CCoindEffect::Start(function<void()> _callback)
{
	SetState(COIN_STATE_MOVE_UP);
	this->callback = _callback;
}

void CCoindEffect::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case  COIN_STATE_MOVE_UP:
		this->vy = -COIN_SPEED_UP;
		break;
	case  COIN_STATE_MOVE_DOWN:
		vy = COIN_SPEED_DOWN;
		break;
	default:
		break;
	}
}

void CCoindEffect::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	switch (state)
	{
	case  COIN_STATE_MOVE_UP:
		if (abs(y - start_y) >= COIN_RETURN_DISTANCE) {
			SetState(COIN_STATE_MOVE_DOWN);
		}
		break;
	case  COIN_STATE_MOVE_DOWN:
		if (y >= start_y - COIN_STOP_DISTANCE) {
			y = start_y;
			vy = 0;
			this->callback();
		}
		break;
	default:
		break;
	}
}
