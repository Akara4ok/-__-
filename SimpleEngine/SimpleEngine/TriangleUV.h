#pragma once
#include "Vector2.h"

class TriangleUV
{
	Vector2 v0;
	Vector2 v1;
	Vector2 v2;
public:
	TriangleUV();
	TriangleUV(Vector2 v0, Vector2 v1, Vector2 v2);
	Vector2 getVertex(int number);
};

