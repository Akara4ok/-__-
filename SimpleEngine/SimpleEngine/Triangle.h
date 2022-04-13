#pragma once
#include "Vector3.h"
#include "Box.h"

class Triangle
{
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
public:
	Triangle();
	Triangle(Vector3 v0, Vector3 v1, Vector3 v2);
	Vector3 getVertex(int number);
	Vector3 getNormal();
	bool inBox(Box b);
};

