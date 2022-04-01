#pragma once
#include "Vector3.h"
#include <vector>
#include "Ray.h"

class Camera
{
	Ray playerView;
	std::vector<std::vector<Vector3>> screenDots;
	float distToScreen;
	float realH, realW;
	float pixelH, pixelW;
public:
	Camera(float distToScreen = 1, float realH = 9, float realW = 16, float pixelH = 1080, float pixelW = 1920);
	void setScreen(Ray playerView);
};

