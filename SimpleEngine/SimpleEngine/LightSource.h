#pragma once
#include "Vector3.h"
#include "BMPStruct.h"

struct LightSource
{
	Vector3 orig;
	Pixel_triplet color;
	float diffCoef;
	int diffMode; // 0 - no diffusion, 1 - cos diffusion, 2 - difussion by cos and dist^2
	LightSource(Vector3 light, Pixel_triplet color, int diffMode = 1, float diffCoef = 0.05) : orig(light), color(color), diffCoef(diffCoef), diffMode(diffMode){}
};

