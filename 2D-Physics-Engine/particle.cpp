#define VECTOR2_H
#define PARTICLE_H
#include "./vector2.h";
#include "./particle.h"
#include "./SFML/Graphics.hpp"

Particle::Particle(Vector2 position, Vector2 velocity)
{
	circle.setRadius(this->radius);
	circle.setPosition(this->position.x, this->position.y);

}

void Particle::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}