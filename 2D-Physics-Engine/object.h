//#ifdef OBJECT_H
#define OBJECT_H
#define VECTOR2_H
#include "./vector2.h"
#include <SFML/Graphics.hpp>

class Object
{
public:
	float mass;
	float radius;
	Vector2 position;
	Vector2 velocity;
	static float damping;
	static Vector2 gravity;

	Object(float r, float m, Vector2 pos, Vector2 v);
	void Simulate(float dt);
	void WindowCollision(sf::RenderWindow& window);

};


//#endif // OBJECT_H

