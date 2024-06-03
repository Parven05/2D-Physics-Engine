#include "vector2.h"

class Object
{
public:
	Vector2 position;
	Vector2 velocity;
	float mass;
	static float damping;
	static Vector2 gravity;
	static float restitution;
	
public:
	Object(Vector2 pos, Vector2 v);
	void Move(float dt);

};


