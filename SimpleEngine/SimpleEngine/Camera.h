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
	Vector3 camera;
	Vector3 dir;
	Vector3** screenDots;
	int pixelH, pixelW;
public:
	Vector3 getOrig();
	Vector3** getScreenDots();
	int getPixelH();
	int getPixelW();
	Camera(float distToScreen = 1, float realH = 9, float realW = 16, int pixelH = 1080, int pixelW = 1920);
	void setScreen(Ray playerView);
	void draw(OctTree octTree, std::vector<Triangle> triangles, int** nTriangle, Vector3** intersectionPoint, Vector3** UVCoord);
};

