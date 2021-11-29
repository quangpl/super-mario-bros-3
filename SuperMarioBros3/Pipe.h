#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Constants.h"
#include "Transformation.h"

enum PipeType {
	Long = 1,
	Short = 2,
};


class CPipe : public CGameObject
{
	Vec2 size;

	Vec2 verticalPeiceSize = Vec2(96, 48);
	Vec2 horizontalPeiceSize = Vec2(48, 96);

	int length;

	float lengthOfPiece;

	Direction direction;

	Transformation trans;

	LPSPRITE head;
	LPSPRITE body;
public:
	CPipe();
	virtual void Render();
	virtual RectBox GetBoundingBox();
	static CPipe* Create(Vec2 pos, Vec2 size, MapData& props);
};

