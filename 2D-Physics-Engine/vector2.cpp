#include "vector2.h"
#include <cmath>

Vector2::Vector2(float init_x, float init_y) : x(init_x), y(init_y) {}

Vector2::Vector2() : x(0), y(0) {}

Vector2 Vector2::scaleAdd(Vector2 v, float s)
{
	x += v.x * s;
	y += v.y * s;
	return Vector2(x, y);
}

Vector2 Vector2::scaleSub(Vector2 v, float s)
{
	x -= v.x * s;
	y -= v.y * s;
	return Vector2(x, y);
}

Vector2 Vector2::scaleDivide(Vector2 v, float s)
{
	x /= v.x * s;
	y /= v.y * s;
	return Vector2(x, y);
}

Vector2 Vector2::addVector(Vector2 v, Vector2 w)
{
	x = v.x + w.x;
	y = v.y + w.y;
	return Vector2(x, y);
}

Vector2 Vector2::subVector(Vector2 v, Vector2 w)
{
	x = v.x - w.x;
	y = v.y - w.y;
	return Vector2(x, y);
}

Vector2 Vector2::scalarMultiVector(Vector2 v, float lambda)
{
	x = lambda * v.x;
	y = lambda * v.y;
	return Vector2(x, y);
}


Vector2 Vector2::scaleVector(float lambda)
{
	x *= lambda;
	y *= lambda;
	return Vector2(x,y);
}

float Vector2::Magnitude()
{
	return (x * x + y * y);
}

float Vector2::DotProduct(Vector2 v)
{
	return x * v.x + y * v.y;
}

Vector2 Vector2::Normalize()
{
	float mag = std::sqrt(x * x + y * y);
	if (mag != 0) {
		return Vector2(x / mag, y / mag);
	}
	else {
		return *this;
	}
}