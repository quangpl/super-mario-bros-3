#pragma once
#include "GameObject.h"
#include "Constants.h"
#define MUSHROOM_GRAVITY			0.0003f
#define MUSHROOM_SPEED_Y	0.05f

#define SUPER_MUSHROOM_ANI	301

class CMushroom :
	public CGameObject
{

public:
	CMushroom(int t);
	~CMushroom();

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
};