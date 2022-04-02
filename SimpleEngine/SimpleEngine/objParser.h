#pragma once
#include <vector>
#include <string>
#include "Triangle.h"

class objParser
{
public:
	static std::vector<Triangle> parseObj(std::string path);
};

