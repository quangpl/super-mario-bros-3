#include "Pipe.h"
#include "Utils.h"
CPipe::CPipe()
{
	this->type = Type::PIPE;
	this->pipe_type = PipeType::Long;
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
CPipe* CPipe::Create(Vec2 pos) {
	CPipe* pipe = new CPipe();
	pipe->position = pos;
	return pipe;
}
void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*int height = pipe_type == PipeType::Long ? PIPE_BBOX_HEIGHT_LONG : PIPE_BBOX_HEIGHT_SHORT;
	l = x - PIPE_BBOX_WIDTH / 2;
	t = y - height / 2;
	r = l + PIPE_BBOX_WIDTH;
	b = t + height;*/
}
