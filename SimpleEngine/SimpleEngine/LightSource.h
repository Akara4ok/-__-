#pragma once
#include "Vector3.h"
#include "BMPStruct.h"

struct LightSource
{
	Vector3 orig;
	Pixel_triplet color;
	LightSource(Vector3 light, Pixel_triplet color) : orig(light), color(color) {}
};

