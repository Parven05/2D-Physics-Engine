#ifdef PARTICLE_H
#define PARTICLE_H

class Particle
{
private:
	const float radius = 20;
	const float speed = 10;
	const float mass = 2;

public:
	sf::CircleShape circle;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	Particle(Vector2 position, Vector2 particle);
	void Draw(sf::RenderWindow& window);

};
#endif