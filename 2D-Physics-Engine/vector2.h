#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float init_x, float init_y);
	Vector2 scaleAdd(Vector2 v, float a);
	Vector2 scaleSub(Vector2 v, float s);
	Vector2 scaleDivide(Vector2 v, float s);
	Vector2 addVector(Vector2 v, Vector2 w);
	Vector2 subVector(Vector2 v, Vector2 w);
	Vector2 scalarMultiVector(Vector2 v, float lambda);
	Vector2 scaleVector(float lambda);
	float Magnitude();
	float DotProduct(Vector2 v);
	Vector2 Normalize();
};