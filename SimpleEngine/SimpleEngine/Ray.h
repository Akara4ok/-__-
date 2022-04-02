#pragma once
#include "Vector3.h"
#include "Triangle.h"

class Ray
{
	Vector3 origin;
	Vector3 dir;
public:
	Ray();
	Ray(Vector3 origin, Vector3 dir);
	Vector3 getOrigin();
	Vector3 getDir();
	float triangleIntersaction(Triangle tr, float& u, float& v);
};

