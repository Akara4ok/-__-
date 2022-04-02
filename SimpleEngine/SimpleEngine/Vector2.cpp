#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(Vector2 startPoint, Vector2 endPoint)
{
	Vector2 res = endPoint - startPoint;
	x = res.x;
	y = res.y;
}

Vector2 Vector2::getOrt()
{
	float absVec = this->absValue();
	return Vector2(x / absVec, y / absVec);
}

float Vector2::absValue()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 vec1)
{
	return Vector2(x + vec1.x, y + vec1.y);
}

Vector2 Vector2::operator-(const Vector2 vec1)
{
	return Vector2(x - vec1.x, y - vec1.y);
}

Vector2 Vector2::operator*(const double a)
{
	return Vector2(a * x, a * y);
}
