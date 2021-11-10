#pragma once
#include "Effect.h"
#include "Animations.h"
#include <functional>

#define COIN_RETURN_DISTANCE 60
#define COIN_STOP_DISTANCE 35
#define COIN_ANI_ROTATION		451

#define COIN_SPEED_UP 0.13f
#define COIN_SPEED_DOWN 0.06f


#define  COIN_STATE_NORMAL		1
#define  COIN_STATE_BROKEN		2
#define  COIN_STATE_MOVE_UP		3
#define  COIN_STATE_MOVE_DOWN	4
#define  COIN_STATE_HIT		5

#define  COIN_SHIP_DISTANCE 4
#define  COIN_REVERT_POSITION_TIME 2000


class CCoindEffect :
    public CEffect
{
    int state;
    float start_y;
public:
    function<void()> callback;
    CCoindEffect(float x, float y);

    virtual void Update(DWORD dt);
    virtual void Render();
    void SetState(int state);
    void Start(function<void()> _callback = 0);
};

