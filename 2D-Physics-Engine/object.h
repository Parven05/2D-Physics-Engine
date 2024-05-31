//#ifdef OBJECT_H
#define OBJECT_H
#define VECTOR2_H
#include "./vector2.h"
#include <SFML/Graphics.hpp>

class Object
{
public:
	static float mass;
	float radius;
	Vector2 position;
	Vector2 velocity;
	static float damping;
	static Vector2 gravity;
	static float restitution;

	Object(float r, Vector2 pos, Vector2 v);
	void Simulate(float dt);

};


//#endif // OBJECT_H

