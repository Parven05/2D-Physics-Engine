#define OBJECT_H
#include "./object.h"
#include <iostream>

float Object::mass = 5.0f;
float Object::damping = 0.0f;
Vector2 Object::gravity = Vector2(0, 0);
float Object::restitution = 1.0f;

Object::Object(float r, Vector2 pos, Vector2 v)
	: radius(r), position(pos), velocity(v) {}

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
void Object::CircleCollision(Object& b)
{
    float dx = b.position.x - position.x;
    float dy = b.position.y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float totalRadius = radius + b.radius;

    if (distance < totalRadius)
    {
        // Step 1: Calculate the collision angle
        float angle = std::atan2(dy, dx);

        // Step 2: Rotate the velocity vectors to the collision coordinate system
        float v1x = velocity.x * std::cos(angle) + velocity.y * std::sin(angle);
        float v1y = velocity.y * std::cos(angle) - velocity.x * std::sin(angle);
        float v2x = b.velocity.x * std::cos(angle) + b.velocity.y * std::sin(angle);
        float v2y = b.velocity.y * std::cos(angle) - b.velocity.x * std::sin(angle);

        // Step 3: Apply 1D collision equation along the x-axis
        float v1PrimeX = (v1x * (mass - b.mass) + 2 * b.mass * v2x) * restitution / (mass + b.mass);
        float v2PrimeX = (v2x * (b.mass - mass) + 2 * mass * v1x)  * restitution / (mass + b.mass);

        // Step 4: Rotate the velocities back to the original coordinate system
        velocity.x = v1PrimeX * std::cos(-angle) + v1y * std::sin(-angle);
        velocity.y = v1y * std::cos(-angle) - v1PrimeX * std::sin(-angle);
        b.velocity.x = v2PrimeX * std::cos(-angle) + v2y * std::sin(-angle);
        b.velocity.y = v2y * std::cos(-angle) - v2PrimeX * std::sin(-angle);

        // Adjust positions to prevent sticking
        float overlap = 0.5f * (totalRadius - distance + 1.0f);  // Add a small value to avoid precision issues
        Vector2 displacement = Vector2(overlap * std::cos(angle), overlap * std::sin(angle));
        position = position.subVector(position, displacement.scaleVector(1.0f));
        b.position = b.position.addVector(b.position, displacement.scaleVector(1.0f));
    }
}
