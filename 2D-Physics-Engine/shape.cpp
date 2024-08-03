#include "shape.h"
#include <iostream>

float Shape::damping = 0.0f;
Vector2 Shape::gravity = Vector2(0, 0);
float Shape::restitution = 1.0f;

Shape::Shape(Vector2 pos, Vector2 v)
	: position(pos), velocity(v) {}

void Shape::Move(float dt)
{
	mass = 5.0f;

	Vector2 force = Vector2(mass * gravity.x, mass * gravity.y);

	velocity.y += force.y * dt;
	velocity.x += force.x * dt;

	position.x += velocity.x * dt;
	position.y += velocity.y * dt;

	if (velocity.x > 0)
	{
		velocity.x = std::max(0.0f, velocity.x - damping * dt);
	}
	if (velocity.y > 0)
	{
		velocity.y = std::max(0.0f, velocity.y - damping * dt);
	}

}
