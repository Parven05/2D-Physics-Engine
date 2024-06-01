#define OBJECT_H
#define CIRCLE_H
#include "./object.h"

class Circle : public Object
{
public:

	float radius;
	Circle(float r, Vector2 pos, Vector2 v);

};
