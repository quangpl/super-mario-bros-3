#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "MapData.h"
#define MARIO_TRANSPORT_PACE 1.1f

class EndPortal :
    public CGameObject
{
public:
    bool isMoving = false;
    EndPortal(Vec2 pos, Vec2 size, MapData data);
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

