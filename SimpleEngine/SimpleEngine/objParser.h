#pragma once
#include <vector>
#include <string>
#include "Triangle.h"
#include "Vector2.h"

class objParser
{
public:
	static void parseObj(std::vector<Triangle>& triangles, std::vector<Vector3>& vertex, std::vector<Vector2>& textureCoord, std::string path);
};

