#pragma once
#include "GameObject.h"
#include "Constants.h"

#define PIPE_ANI_LONG		1001
#define PIPE_ANI_SHORT		1002
#define BLACK_ANI_SHORT		1003

#define PIPE_BBOX_WIDTH			32
#define PIPE_BBOX_HEIGHT_LONG	48
#define PIPE_BBOX_HEIGHT_SHORT	32

enum PipeType {
	Long = 1,
	Short = 2,
};


class CPipe : public CGameObject
{
	int pipe_type;
	bool direction;
public:
	CPipe();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	static CPipe* Create(Vec2 pos);
};

