#define SANDBOX_H
#define SOLVER_H
#include "./solver.h"

class Sandbox
{
public:
	sf::RenderWindow window;
	sf::ContextSettings settings;
	sf::CircleShape ballShape;
	Solver solver;
	sf::Clock clock;

	void Start();
	void Update();

};