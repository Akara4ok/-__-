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
