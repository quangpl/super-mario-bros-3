#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mario.h"

class CGround :public CGameObject
{
	int width;
	int height;
	Vec2 size;
	bool fullBlock = false;
public:
	// fullBlock : va cham 4 mat
	static CGround* Create(Vec2 position, Vec2 size, bool fullBlock);
	bool interact;
	virtual void Render();
	CGround();
	bool CanThrough(CGameObject* gameObject, float collisionNx, float collisionNy);
	~CGround();

	RectBox GetBoundingBox()
	{
		bounding_box.left = position.x ;
		bounding_box.top = position.y ;
		bounding_box.right = position.x + size.x;
		bounding_box.bottom = position.y + size.y;
		return bounding_box;
	}
};
