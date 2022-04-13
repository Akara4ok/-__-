#include "Ray.h"
#include <algorithm>

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

float Ray::triangleIntersection(Triangle tr, float& u, float& v)
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
	u = Vector3::dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}

	Vector3 qvec = Vector3::cross(tvec, e1);
	v = Vector3::dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return 0;
	}
	float t = Vector3::dot(e2, qvec) * inv_det;
	if (t < 0)
		return 0;
	return (dir * t).absValue();
}

float Ray::boxIntersaction(Box b)
{

	Vector3 dirfrac(1.0f / dir.x, 1.0f / dir.y, 1.0f / dir.z);

	float t1 = (b.getMin().x - origin.x) * dirfrac.x;
	float t2 = (b.getMax().x - origin.x) * dirfrac.x;
	float t3 = (b.getMin().y - origin.y) * dirfrac.y;
	float t4 = (b.getMax().y - origin.y) * dirfrac.y;
	float t5 = (b.getMin().z - origin.z) * dirfrac.z;
	float t6 = (b.getMax().z - origin.z) * dirfrac.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax < 0)
	{
		return false;
	}

	if (tmin > tmax)
	{
		return false;
	}

	return true;
}
