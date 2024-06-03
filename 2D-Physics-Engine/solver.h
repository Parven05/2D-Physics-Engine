#include "circle.h"
#include <SFML/Graphics.hpp>

class Solver
{
public:
	void WindowCollision(sf::RenderWindow& window, Circle& circle);
	void CircleCollision(Circle& a, Circle& b);
};