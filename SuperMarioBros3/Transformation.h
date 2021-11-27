#pragma once
#include "Utils.h"

class Transformation
{
public:
	Vec2 Position;
	Vec2 Scale;
	float Rotation;

	Transformation() { this->Rotation = 0.0f; this->Scale = Vec2(1.0f, 1.0f); };
	Transformation(Vec2 scale, float rotation) { this->Scale = scale; this->Rotation = rotation; }
};
