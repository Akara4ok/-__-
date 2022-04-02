#include "TriangleUV.h"

TriangleUV::TriangleUV()
{
}

TriangleUV::TriangleUV(Vector2 v0, Vector2 v1, Vector2 v2) : v0(v0), v1(v1), v2(v2)
{
}

Vector2 TriangleUV::getVertex(int number)
{
	if (number == 0)
		return v0;
	else if (number == 1)
		return v1;
	else if (number == 2)
		return v2;
}
