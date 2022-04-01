#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(Vector3 startPoint, Vector3 endPoint)
{
	Vector3 res = endPoint - startPoint;
	x = res.x;
	y = res.y;
	z = res.z;	
}

Vector3 Vector3::getOrt()
{
	float absVec = this->absValue();
	return Vector3(x / absVec, y / absVec, z / absVec);
}

float Vector3::absValue()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::dot(Vector3 vec1, Vector3 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 Vector3::cross(Vector3 vec1, Vector3 vec2)
{
	return Vector3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3 vec1)
{
	return Vector3(x + vec1.x, y + vec1.y, z + vec1.z);
}

Vector3 Vector3::operator-(const Vector3 vec1)
{
	return Vector3(x - vec1.x, y - vec1.y, z - vec1.z);
}

Vector3 Vector3::operator*(const double a)
{
	return Vector3(a * x, a * y, a * z);
}
