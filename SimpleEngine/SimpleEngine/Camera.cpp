#include "Camera.h"
#include <math.h>
#include "Vector2.h"
#include <utility>

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

	float a, b, c, d; //plane equation for screen
	Vector3 n = dir.getOrt();
	a = n.x;
	b = n.y;
	c = n.z;
	float s = Vector3::dot(-camera, dir) > 0 ? 1 : -1;
	float l = Vector3::dot(camera, dir) / dir.absValue();
	d = -(distToScreen - (Vector3::dot(-camera, dir) > 0 ? 1 : -1) * abs(Vector3::dot(camera, dir) / dir.absValue()));


	float t; //center of the screen
	t = -(a * camera.x + b * camera.y + c * camera.z + d) / (a * dir.x + b * dir.y + c * dir.z);
	Vector3 center(camera.x + dir.x * t, camera.y + dir.y * t, camera.z + dir.z * t);

	Vector3 right = (Vector3::cross(dir, Vector3(0, 1, 0))).getOrt(); //two ortogonal vector for screen
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

std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> Camera::draw(std::vector<Triangle> triangles)
{
	std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> res(pixelH, std::vector < std::pair<std::pair<int, Vector3>, Vector3>>(pixelW, std::make_pair(std::make_pair(-1, Vector3(0, 0, 0)), Vector3(0, 0, 0))));

	for (size_t i = 0; i < pixelH; i++)
	{
		for (size_t j = 0; j < pixelW; j++)
		{
			float min = 100000;
			for (size_t k = 0; k < triangles.size(); k++)
			{
				float u, v;
				float dist = Ray(camera, (screenDots[i][j] - camera)).triangleIntersaction(triangles[k], u, v);
				if (dist && min > dist)
				{
					res[i][j] = std::make_pair(std::make_pair(k, camera + (screenDots[i][j] - camera).getOrt() * dist), Vector3(1 - u - v, u, v));
					min = dist;
				}
			}
		}
	}
	return res;
}
