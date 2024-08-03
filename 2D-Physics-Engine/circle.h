#pragma once
#include "shape.h"

struct Circle : public Shape
{
	float radius;

	Circle(float r, Vector2 pos, Vector2 v);

};
