#pragma once
#include "Effect.h"
#include "Animations.h"
#include "Transformation.h"
#include <functional>

#define SCORE_SPEED -0.2f

#define SCRORE_SIZE 48

#define SCORE_STATE_HIDE 0
#define SCORE_STATE_MOVE 1

#define SCORE_HIDE_DISTANCE 48*2

enum class ScoreNum
{
	SCORE100 = 100,
	SCORE200 = 200,
	SCORE400 = 400,
	SCORE800 = 800,
	SCORE1000 = 1000,
	SCORE2000 = 2000,
	SCORE4000 = 4000,
	SCORE8000 = 8000
};

class ScoreEffect :
	public CEffect
{
	ScoreNum score = ScoreNum::SCORE100;
	Transformation trans;
	int state;
	float start_y;
public:
	function<void()> callback;
	ScoreEffect(float x, float y, ScoreNum score);

	virtual void Update(DWORD dt);
	virtual void Render();
	void SetState(int state);
	void Start(function<void()> _callback = 0);
};

