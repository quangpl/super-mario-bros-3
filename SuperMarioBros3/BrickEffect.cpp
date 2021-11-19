#include "BrickEffect.h"

CBrickEffect::CBrickEffect(float _x, float _y) : CEffect(_x, _y)
{
	this->start_y = _y;
}

void CBrickEffect::Render()
{
	//CAnimations::GetInstance()->Get(BRICK_ANI_BROKEN)->Render(x, y);
}

void CBrickEffect::Start(function<void()> _callback)
{
	SetState(BRICK_STATE_MOVE_UP);
	this->callback = _callback;
}

void CBrickEffect::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case BRICK_STATE_MOVE_UP:
		this->vy = -BRICK_SPEED;
		break;
	case BRICK_STATE_MOVE_DOWN:
		vy = BRICK_SPEED;
		break;
	default:
		break;
	}
}

void CBrickEffect::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	//DebugOut(L"start_y: %f, y:%f \n", start_y, y);
	switch (state)
	{
	case BRICK_STATE_MOVE_UP:
		if (abs(y - start_y) >= BRICK_RETURN_DISTANCE) {
			SetState(BRICK_STATE_MOVE_DOWN);
		}
		break;
	case BRICK_STATE_MOVE_DOWN:
		if (y >= start_y) {
			y = start_y;
			vy = 0;
			this->callback();
		}
		break;
	default:
		break;
	}
}
