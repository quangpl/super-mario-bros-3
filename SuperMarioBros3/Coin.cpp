#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(COIN_ANI_ROTATION)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
	switch (state)
	{
	case COIN_STATE_MOVE_UP:
		if (abs(y - start_y) >= COIN_RETURN_DISTANCE) {
			SetState(COIN_STATE_MOVE_DOWN);
		}
		break;
	case COIN_STATE_MOVE_DOWN:
		if (abs(y - start_y) <= COIN_HIDE_DISTANCE) {
			isDeleted = true;
		}
		break;
	default:
		break;
	}
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_MOVE_UP:
		start_y = y;
		vy = -COIN_SPEED;
		break;
	case COIN_STATE_MOVE_DOWN:
		vy = COIN_SPEED / 2;
		break;
	default:
		break;
	}
}