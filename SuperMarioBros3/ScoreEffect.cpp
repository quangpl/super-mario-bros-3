#include "ScoreEffect.h"


ScoreEffect::ScoreEffect(float _x, float _y, ScoreNum score) : CEffect(_x, _y)
{
	this->start_y = _y;
	this->state = SCORE_STATE_HIDE;
	this->score = score;
}

void ScoreEffect::Render()
{
	if (this->state == SCORE_STATE_HIDE) {
		return;
	}
	string spr = "spr-points-in-level-100";
	switch (score)
	{
	case ScoreNum::SCORE100:
		spr = "spr-points-in-level-100";
		break;
	case ScoreNum::SCORE200:
		spr = "spr-points-in-level-200";
		break;
	case ScoreNum::SCORE400:
		spr = "spr-points-in-level-400";
		break;
	case ScoreNum::SCORE800:
		spr = "spr-points-in-level-800";
		break;
	case ScoreNum::SCORE1000:
		spr = "spr-points-in-level-1000";
		break;
	case ScoreNum::SCORE2000:
		spr = "spr-points-in-level-2000";
		break;
	case ScoreNum::SCORE4000:
		spr = "spr-points-in-level-4000";
		break;
	case ScoreNum::SCORE8000:
		spr = "spr-points-in-level-8000";
		break;
	default:
		break;
	}
	CSprites::GetInstance()->Get(spr)->Draw(x + 24, y + 24, trans, 1.0f);
}

void ScoreEffect::Start(function<void()> _callback)
{
	SetState(SCORE_STATE_MOVE);
	this->vy = SCORE_SPEED;
	this->callback = _callback;
}

void ScoreEffect::SetState(int state)
{
	this->state = state;
}

void ScoreEffect::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (state == SCORE_STATE_MOVE && abs(y - start_y) >= SCORE_HIDE_DISTANCE) {
		this->SetState(SCORE_STATE_HIDE);
		this->callback();
	}
}
