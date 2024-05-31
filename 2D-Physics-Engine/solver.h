#define SOLVER_H
#define OBJECT_H
#include "object.h"


class Solver
{
public:
	void WindowCollision(sf::RenderWindow& window, Object& object);
	void CircleCollision(Object& a,Object& b);
};