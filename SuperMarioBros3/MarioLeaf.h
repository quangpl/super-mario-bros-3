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
#define LEAF_GRAVITY  0.0012f
#define LEAF_REVEAL_DISTANCE 72 //48 * 1.5f
#define LEAF_REVEAL_FORCE 0.03f
#define  LEAF_FALLING_VEL 0.065f

class MarioLeaf : public CGameObject
{
public:
	int fallingStep = 0;
	Vec2 startingPos;
	void OnNoCollision(DWORD dt);
	MarioLeaf(Vec2 pos);
	~MarioLeaf();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects) override;
	void SetState(int state);
};