#define OBJECT_H
#include "./object.h"
#include <iostream>

float Object::mass = 5.0f;
float Object::damping = 0.0f;
Vector2 Object::gravity = Vector2(0, 0);
float Object::restitution = 1.0f;

Object::Object(Vector2 pos, Vector2 v)
	: position(pos), velocity(v) {}


void Object::Simulate(float dt)
{
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
