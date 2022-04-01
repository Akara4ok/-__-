#include "Camera.h"

Camera::Camera(float distToScreen, float realH, float realW, float pixelH, float pixelW) : distToScreen(distToScreen), realH(realH), realW(realW), pixelH(pixelH), pixelW(pixelW)
{
	screenDots = std::vector<std::vector<Vector3>>(pixelH, std::vector<Vector3>(pixelW));
}

void Camera::setScreen(Ray playerView) {
	this->playerView = playerView;
	Vector3 dir = playerView.getDir();
	Vector3 camera = playerView.getOrigin();

	float a, b, c, d; //plane equation for screen
	Vector3 n = dir.getOrt();
	a = n.x;
	b = n.y;
	c = n.z;
	d = -(distToScreen - (Vector3::dot(-camera, dir) > 0 ? 1 : -1) * Vector3::dot(camera, dir) / dir.absValue());

	float t; //center of the screen
	t = -(a * camera.x + b * camera.y + c * camera.z + d) / (a * dir.x + b * dir.y + c * dir.z);
	Vector3 center(camera.x + dir.x * t, camera.y + dir.y * t, camera.z + dir.z * t);

	Vector3 right = (Vector3::cross(Vector3(0, 0, 1), dir)).getOrt(); //two ortogonal vector for screen
	Vector3 up = (Vector3::cross(dir, right)).getOrt();

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
