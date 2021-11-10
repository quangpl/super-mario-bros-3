#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mario.h"

class CGround :public CGameObject
{
	int width;
	int height;

public:
	bool interact;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CGround(int w, int h, bool i);
	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);
	~CGround();
};
