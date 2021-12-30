#include "BrickEffect.h"
#include "Brick.h"

CBrickEffect::CBrickEffect(float _x, float _y) : CEffect(_x, _y)
{
	this->state = -1;
	this->start_y = _y;
}

void CBrickEffect::Render()
{
	CAnimations::GetInstance()->Get("ani-empty-block")->Render(x + BRICK_BBOX_WIDTH/2, y + BRICK_BBOX_HEIGHT/2);
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
