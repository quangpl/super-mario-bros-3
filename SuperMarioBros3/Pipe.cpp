#include "Pipe.h"
#include "Utils.h"
CPipe::CPipe(int pipe_type, bool direction)
{
	this->type = Type::PIPE;
	this->pipe_type = pipe_type;
	this->direction = direction;
}

void CPipe::Render()
{
	if (pipe_type == PipeType::Long)
		ani = PIPE_ANI_LONG;
	else
	{
		if (direction)
			ani = BLACK_ANI_SHORT;
		else
			ani = PIPE_ANI_SHORT;
	}
	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*int height = pipe_type == PipeType::Long ? PIPE_BBOX_HEIGHT_LONG : PIPE_BBOX_HEIGHT_SHORT;
	l = x - PIPE_BBOX_WIDTH / 2;
	t = y - height / 2;
	r = l + PIPE_BBOX_WIDTH;
	b = t + height;*/
}
