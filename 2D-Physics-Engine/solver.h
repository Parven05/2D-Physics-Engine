#pragma once
#include "circle.h"
#include <SFML/Graphics.hpp>

struct Solver
{
	void WindowCollision(sf::RenderWindow& window, Circle& circle);
	void CircleCollision(Circle& a, Circle& b);
};