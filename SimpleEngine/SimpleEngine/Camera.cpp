#include "Camera.h"
#include <math.h>
#include "Vector2.h"
#include <utility>
#include <iostream>

Vector3 Camera::getOrig()
{
	return camera;
}

Vector3** Camera::getScreenDots()
{
	return screenDots;
}

int Camera::getPixelH()
{
	return pixelH;
}

int Camera::getPixelW()
{
	return pixelW;
}

Camera::Camera(float distToScreen, float realH, float realW, int pixelH, int pixelW) : distToScreen(distToScreen), realH(realH), realW(realW), pixelH(pixelH), pixelW(pixelW)
{
	screenDots = new Vector3* [pixelH];
	for (int i = 0; i < pixelH; i++)
	{
		screenDots[i] = new Vector3[pixelW];
	}
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

void Camera::draw(OctTree octTree, std::vector<Triangle> triangles, int** nTriangle, Vector3** intersectionPoint, Vector3** UVCoord)
{
	for (size_t i = 0; i < pixelH; i++)
	{
		for (size_t j = 0; j < pixelW; j++)
		{
			int k;
			float u, v, dist;
			dist = 10000;
			Ray r(camera, (screenDots[i][j] - camera));
			if (octTree.findMinIntersection(r, k, dist, u, v))
			{
				nTriangle[i][j] = k;
				intersectionPoint[i][j] = camera + (screenDots[i][j] - camera).getOrt() * dist;
				UVCoord[i][j] = Vector3(1 - u - v, u, v);
			}
		}
	}
}
