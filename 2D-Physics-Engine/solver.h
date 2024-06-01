#define CIRCLE_H
#include "circle.h"
#include <SFML/Graphics.hpp>
//#include <algorithm>


class Solver
{
public:
	void WindowCollision(sf::RenderWindow& window, Circle& circle);
	void CircleCollision(Circle& a, Circle& b);
};