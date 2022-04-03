#pragma once
#include <vector>
#include <string>
#include "Triangle.h"
#include "TriangleUV.h"
#include "Vector2.h"
#include "BMPStruct.h"
#include <map>

class objParser
{
public:
	static void parseObj(std::vector<Triangle>& triangles, std::vector<std::string>& trianglesTextureName, std::vector<TriangleUV>& trianglesTexture, std::map<std::string, std::vector<std::vector<Pixel_triplet>>>& textures, std::string path, std::string file_name);
};

