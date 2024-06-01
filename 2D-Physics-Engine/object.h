//#ifdef OBJECT_H
#define OBJECT_H
#define VECTOR2_H
#include "./vector2.h"

class Object
{
public:
	Vector2 position;
	Vector2 velocity;

	static float mass;
	static float damping;
	static Vector2 gravity;
	static float restitution;

	Object(Vector2 pos, Vector2 v);
	void Simulate(float dt);

};


//#endif // OBJECT_H

