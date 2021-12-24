#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Animations.h"
#include "SceneManager.h"
#include "Mario.h"
#include "ObjectType.h"
#include "ObjectTypeData.h"

#define LEAF_SIZE 45
#define  LEAF_GROWUP_SPEED  0.0012f
#define LEAF_GRAVITY  0.00035f
#define LEAF_REVEAL_DISTANCE 72
#define LEAF_REVEAL_FORCE 0.02f
#define  LEAF_FALLING_VEL 0.05f

class MarioLeaf : public CGameObject
{
public:
	int fallingStep = 0;
	Vec2 startingPos;
	virtual void OnNoCollision(DWORD dt);
	MarioLeaf(Vec2 pos);
	~MarioLeaf();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual bool CanThrough(CGameObject* gameObjToCollide, float coEventNx, float coEventNy);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
};