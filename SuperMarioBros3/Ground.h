#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mario.h"

class CGround :public CGameObject
{
	int width;
	int height;
	Vec2 size;
public:
	static shared_ptr<CGround> Create(Vec2 position, Vec2 size);
	bool interact;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CGround();
	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);
	~CGround();

	RectBox GetBoundingBox()
	{
		bounding_box.left = position.x;
		bounding_box.top = position.y;
		bounding_box.right = position.x + size.x;
		bounding_box.bottom = position.y + size.y;
		return bounding_box;
	}
};
