#include "solver.h"

class Sandbox
{
public:
	void InitializeBalls(int totalBalls, float radius, sf::RenderWindow& window);
	void Simulate(Solver& solver, sf::RenderWindow& window, float dt);
	void DrawBalls(sf::RenderWindow& window);

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape ballShape;
	std::vector<Circle> balls;
};
