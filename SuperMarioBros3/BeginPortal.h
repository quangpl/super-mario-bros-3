#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "MapData.h"

#define PORTAL_STATE_IDLE 1
#define PORTAL_STATE_TRANSPORT 2
#define PORTAL_STATE_DROP 3
#define MARIO_TRANSPORT_PACE 1.1f
class BeginPortal :
    public CGameObject
{
public:
    bool isMoving = false;
    Vec2 startPos;
    BeginPortal(Vec2 pos, Vec2 size, MapData data);
    virtual RectBox GetBoundingBox();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
    virtual void Render() override;
    virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
protected:
    int cameraRegionId = 0;
    Vec2 size;
    Vec2 destination;
    Direction direction;
};

