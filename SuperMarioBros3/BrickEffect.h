#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>

#define BRICK_RETURN_DISTANCE 5
#define BRICK_ANI_NORMAL		702
#define BRICK_ANI_BROKEN		703

#define BRICK_SPEED 0.1f

#define BRICK_STATE_NORMAL		1
#define BRICK_STATE_BROKEN		2
#define BRICK_STATE_MOVE_UP		3
#define BRICK_STATE_MOVE_DOWN	4
#define BRICK_STATE_HIT		5

// TODO: need improve with Effect
#define BRICK_SHIP_DISTANCE 4
#define BRICK_REVERT_POSITION_TIME 2000

#define BRICK_ANI_BROKEN    703

class CBrickEffect :
    public CEffect
{
    int state;
    float start_y;
public:
    function<void()> callback;
    CBrickEffect(float x, float y);

    virtual void Update(DWORD dt);
    virtual void Render();
    void SetState(int state);
    void Start(function<void()> _callback = 0);
};

