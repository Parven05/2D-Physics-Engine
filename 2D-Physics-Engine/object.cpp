#define OBJECT_H
#include "./object.h"
#include <iostream>

Object::Object(float r, float m, Vector2 pos, Vector2 v)
	: radius(r), mass(m), position(pos), velocity(v) {}

void Object::Simulate(float dt)
{
	Vector2 gravity = Vector2(0, 100);
	Vector2 force = Vector2(0, mass * gravity.y);
	float damping = 50.0f;

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

void Object::WindowCollision(sf::RenderWindow& window)
{
	if (position.x - radius < 0 || position.x + radius > window.getSize().x) {
		position.x = std::clamp(position.x, radius, window.getSize().x - radius);
		velocity.x = -velocity.x;
	}

	if (position.y - radius < 0 || position.y + radius > window.getSize().y) {
		position.y = std::clamp(position.y, radius, window.getSize().y - radius);
		velocity.y = -velocity.y;
	}
}