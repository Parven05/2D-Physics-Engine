#include "object.h"

class Circle : public Object
{
public:
	float radius;

public:
	Circle(float r, Vector2 pos, Vector2 v);

};
