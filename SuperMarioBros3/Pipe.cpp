#include "Pipe.h"
#include "Utils.h"
CPipe::CPipe()
{
	this->type = Type::PIPE;
	zIndex = 10;
}

void CPipe::Render()
{
	if (!head || !body) return;
	switch (direction)
	{
	case Direction::Left:
		head->Draw(position.x + horizontalPeiceSize.x / 2, position.y + horizontalPeiceSize.y / 2, trans, 1.0f);
		for (int i = position.x + lengthOfPiece; i < position.x + size.x - 1; i += lengthOfPiece) {
			body->Draw(i + horizontalPeiceSize.x / 2, position.y + horizontalPeiceSize.y / 2, trans, 1.0f);
		}
		break;

	case Direction::Right:
		head->Draw(position.x + size.x - lengthOfPiece + horizontalPeiceSize.x / 2, position.y + horizontalPeiceSize.y / 2, trans, 1.0f);
		for (int i = position.x; i < position.x + size.x - lengthOfPiece - 1; i += lengthOfPiece) {
			body->Draw(i + horizontalPeiceSize.x / 2, position.y + horizontalPeiceSize.y / 2, trans, 1.0f);
		}
		break;
	case Direction::Bottom:
		head->Draw(position.x + verticalPeiceSize.x / 2, position.y + size.y - lengthOfPiece + verticalPeiceSize.y / 2, trans, 1.0f);
		for (int i = position.y; i < position.y + size.y - lengthOfPiece - 1; i += lengthOfPiece) {
			body->Draw(position.x + verticalPeiceSize.x / 2, i + verticalPeiceSize.y / 2, trans, 1.0f);
		}
		break;
	case Direction::Top:
		head->Draw(position.x + verticalPeiceSize.x / 2, position.y + verticalPeiceSize.y / 2, trans, 1.0f);
		for (int i = position.y + lengthOfPiece; i < position.y + size.y - 1; i += lengthOfPiece) {
			body->Draw(position.x + verticalPeiceSize.x / 2, i + verticalPeiceSize.y / 2, trans, 1.0f);
		}
		break;
	}
	RenderBoundingBox();
}
RectBox CPipe::GetBoundingBox() {
	return this->bounding_box;
}

CPipe* CPipe::Create(Vec2 pos, Vec2 size, MapData& props) {
	CPipe* pipe = new CPipe();
	pipe->position = pos;
	pipe->size = size;
	pipe->bounding_box = RectBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	pipe->length = props.GetInt("Length");
	string direction = "vertical";

	switch (props.GetInt("Direction"))
	{
	case 1:
		pipe->direction = Direction::Top;
		pipe->lengthOfPiece = size.y / pipe->length;
		direction = "vertical";
		break;
	case 2:
		pipe->direction = Direction::Bottom;
		pipe->lengthOfPiece = size.y / pipe->length;
		direction = "vertical";
		break;
	case 3:
		pipe->direction = Direction::Left;
		pipe->lengthOfPiece = size.x / pipe->length;
		direction = "horizontal";
		break;
	case 4:
		pipe->direction = Direction::Right;
		pipe->lengthOfPiece = size.x / pipe->length;
		direction = "horizontal";
		break;
	}

	int type = props.GetInt("Type");

	pipe->head = CSprites::GetInstance()->Get("spr-pipe-" + to_string(type) + "-" + direction + "-head");
	pipe->body = CSprites::GetInstance()->Get("spr-pipe-" + to_string(type) + "-" + direction + "-body");
	return pipe;
}
