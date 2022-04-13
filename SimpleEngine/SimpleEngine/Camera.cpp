#include "Camera.h"
#include <math.h>
#include "Vector2.h"
#include <utility>
#include <iostream>

Vector3 Camera::getOrig()
{
	return camera;
}

Camera::Camera(float distToScreen, float realH, float realW, float pixelH, float pixelW) : distToScreen(distToScreen), realH(realH), realW(realW), pixelH(pixelH), pixelW(pixelW)
{
	screenDots = std::vector<std::vector<Vector3>>(pixelH, std::vector<Vector3>(pixelW));
}

void Camera::setScreen(Ray playerView) {
	dir = playerView.getDir();
	camera = playerView.getOrigin();
	Vector3 n = dir.getOrt();
	Vector3 distVector = n * distToScreen;
	Vector3 center(camera.x + distVector.x, camera.y + distVector.y, camera.z + distVector.z);
	Vector3 notNormalizedRight = Vector3::cross(dir, Vector3(0, 1, 0));
	if (std::abs(notNormalizedRight.x) < 0.0001 && std::abs(notNormalizedRight.y) < 0.0001 && std::abs(notNormalizedRight.z) < 0.0001)
		notNormalizedRight = Vector3(-1, 0, 0);
	Vector3 right = (notNormalizedRight).getOrt(); //two ortogonal vector for screen
	Vector3 up = (Vector3::cross(right, dir)).getOrt();

	Vector3 corner = right * (-realW / 2) + center; //find left-down corner
	corner = up * (-realH / 2) + corner;

	float resolution = realH / pixelH; //fill screen with dots
	for (size_t i = 0; i < pixelH; i++)
	{
		for (size_t j = 0; j < pixelW; j++)
		{
			screenDots[i][j] = up * i * resolution + (right * j * resolution + corner);
		}
	}
}

std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> Camera::draw(OctTree octTree, std::vector<Triangle> triangles)
{
	std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> res(pixelH, std::vector < std::pair<std::pair<int, Vector3>, Vector3>>(pixelW, std::make_pair(std::make_pair(-1, Vector3(0, 0, 0)), Vector3(0, 0, 0))));

	for (size_t i = 0; i < pixelH; i++)
	{
		for (size_t j = 0; j < pixelW; j++)
		{
			int k;
			float u, v, dist;
			dist = 10000;
			Ray r(camera, (screenDots[i][j] - camera));
			if(octTree.findMinIntersection(r, k, dist, u, v))
				res[i][j] = std::make_pair(std::make_pair(k, camera + (screenDots[i][j] - camera).getOrt() * dist), Vector3(1 - u - v, u, v));
		}
	}
	return res;
}
