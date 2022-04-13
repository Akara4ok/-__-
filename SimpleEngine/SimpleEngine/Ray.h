#pragma once
#include "Vector3.h"
#include "Triangle.h"
#include "Box.h"

class Ray
{
	Vector3 origin;
	Vector3 dir;
public:
	Ray();
	Ray(Vector3 origin, Vector3 dir);
	Vector3 getOrigin();
	Vector3 getDir();
	float triangleIntersection(Triangle tr, float& u, float& v);
	float boxIntersaction(Box b);
};

