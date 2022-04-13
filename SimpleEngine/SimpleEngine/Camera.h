#pragma once
#include "Vector3.h"
#include <vector>
#include "Ray.h"
#include "Triangle.h"
#include "OctTree.h"

class Camera
{
	float distToScreen;
	float realH, realW;
public:
	Vector3 camera;
	float pixelH, pixelW;
	Vector3 dir;
	std::vector<std::vector<Vector3>> screenDots;
	Vector3 getOrig();
	Camera(float distToScreen = 1, float realH = 9, float realW = 16, float pixelH = 1080, float pixelW = 1920);
	void setScreen(Ray playerView);
	std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> draw(OctTree octTree, std::vector<Triangle> triangles);
};

