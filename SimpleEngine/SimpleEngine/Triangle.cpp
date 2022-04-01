#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2) : v0(v0), v1(v1), v2(v2)
{
}

Vector3 Triangle::getVertex(int number)
{
	if (number == 0)
		return v0;
	else if (number == 1)
		return v1;
	else if (number == 2)
		return v2;
}
