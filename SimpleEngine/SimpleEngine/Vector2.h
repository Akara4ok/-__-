#pragma once
struct Vector2
{
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	Vector2(Vector2 startPoint, Vector2 endPoint);
	Vector2 getOrt();
	static float dot(Vector2 vec1, Vector2 vec2);
	float absValue();
	Vector2 operator-();
	Vector2 operator+(const Vector2 vec1);
	Vector2 operator-(const Vector2 vec1);
	Vector2 operator*(const double a);
};

