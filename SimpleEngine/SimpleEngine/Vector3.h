#pragma once
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(Vector3 startPoint, Vector3 endPoint);
	Vector3 getOrt();
	float absValue();
	static float dot(Vector3 vec1, Vector3 vec2);
	static float getCos(Vector3 vec1, Vector3 vec2);
	static Vector3 cross(Vector3 vec1, Vector3 vec2);
	Vector3 operator-();
	Vector3 operator+(const Vector3 vec1);
	Vector3 operator-(const Vector3 vec1);
	Vector3 operator*(const float a);
};