#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(Vector3 origin, Vector3 dir) : origin(origin), dir(dir)
{
}

Vector3 Ray::getOrigin()
{
	return origin;
}

Vector3 Ray::getDir()
{
	return dir;
}

float Ray::triangleIntersaction(Triangle tr)
{
	Vector3 v0 = tr.getVertex(0);
	Vector3 v1 = tr.getVertex(1);
	Vector3 v2 = tr.getVertex(2);

	Vector3 e1 = v1 - v0;
	Vector3 e2 = v2 - v0;

	Vector3 pvec = Vector3::cross(dir, e2);
	float det = Vector3::dot(e1, pvec);
	

	if (det < 1e-8 && det > -1e-8) {
		return 0;
	}

	float inv_det = 1 / det;
	Vector3 tvec = origin - v0;
	float u = Vector3::dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}

	Vector3 qvec = Vector3::cross(tvec, e1);
	float v = Vector3::dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return 0;
	}
	float t = Vector3::dot(e2, qvec) * inv_det;
	if (t < 0)
		return 0;
	return (dir * t).absValue();
}
