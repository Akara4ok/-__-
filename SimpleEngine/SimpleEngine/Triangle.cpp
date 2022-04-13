#include "Triangle.h"
#include <cmath>
#include <algorithm>

Triangle::Triangle()
{
}

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2) : v0(v0), v1(v1), v2(v2)
{
}

Vector3 Triangle::getVertex(int number)
{
	if (number == 0)
		return v0;
	else if (number == 1)
		return v1;
	else if (number == 2)
		return v2;
}

Vector3 Triangle::getNormal()
{
	return Vector3::cross(Vector3(v0, v1), Vector3(v0, v2));
}

bool Triangle::inBox(Box box)
{
    Vector3 c = (Vector3(box.getMin()) + Vector3(box.getMax())) * 0.5;
    float e0 = (box.getMax().x - box.getMin().x) * 0.5;
    float e1 = (box.getMax().y - box.getMin().y) * 0.5;
    float e2 = (box.getMax().z - box.getMin().z) * 0.5;

    Vector3 vn0 = Vector3(v0) - c;
    Vector3 vn1 = Vector3(v1) - c;
    Vector3 vn2 = Vector3(v2) - c;

    Vector3 f0 = Vector3(v1) - Vector3(v0);
    Vector3 f1 = Vector3(v2) - Vector3(v1);
    Vector3 f2 = Vector3(v0) - Vector3(v2);

    Vector3 a00;
    a00.x = 0;
    a00.y = -f0.z;
    a00.z = f0.y;

    float p0 = Vector3::dot(vn0, a00);
    float p1 = Vector3::dot(vn1, a00);
    float p2 = Vector3::dot(vn2, a00);
    float r = e1 * std::abs(f0.z) + e2 * std::abs(f0.y);
    if (std::max(-std::max(p2, std::max(p0, p1)), std::min(std::min(p0, p1), p2)) > r)
    {

        return false;
    }

    Vector3 a01;
    a01.x = 0;
    a01.y = -f1.z;
    a01.z = f1.y;

    p0 = Vector3::dot(vn0, a01);
    p1 = Vector3::dot(vn1, a01);
    p2 = Vector3::dot(vn2, a01);
    r = e1 * std::abs(f1.z) + e2 * std::abs(f1.y);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }


    Vector3 a02;
    a02.x = 0;
    a02.y = -f2.z;
    a02.z = f2.y;

    p0 = Vector3::dot(vn0, a02);
    p1 = Vector3::dot(vn1, a02);
    p2 = Vector3::dot(vn2, a02);
    r = e1 * std::abs(f2.z) + e2 * std::abs(f2.y);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a10;
    a10.x = f0.z;
    a10.y = 0;
    a10.z = -f0.x;

    p0 = Vector3::dot(vn0, a10);
    p1 = Vector3::dot(vn1, a10);
    p2 = Vector3::dot(vn2, a10);
    r = e0 * std::abs(f0.z) + e2 * std::abs(f0.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a11;
    a11.x = f1.z;
    a11.y = 0;
    a11.z = -f1.x;

    p0 = Vector3::dot(vn0, a11);
    p1 = Vector3::dot(vn1, a11);
    p2 = Vector3::dot(vn2, a11);
    r = e0 * std::abs(f1.z) + e2 * std::abs(f1.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a12;
    a12.x = f2.z;
    a12.y = 0;
    a12.z = -f2.x;

    p0 = Vector3::dot(vn0, a12);
    p1 = Vector3::dot(vn1, a12);
    p2 = Vector3::dot(vn2, a12);
    r = e0 * std::abs(f2.z) + e2 * std::abs(f2.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a20;
    a20.x = -f0.y;
    a20.y = f0.x;
    a20.z = 0;

    p0 = Vector3::dot(vn0, a20);
    p1 = Vector3::dot(vn1, a20);
    p2 = Vector3::dot(vn2, a20);
    r = e0 * std::abs(f0.y) + e1 * std::abs(f0.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a21;
    a21.x = -f1.y;
    a21.y = f1.x;
    a21.z = 0;

    p0 = Vector3::dot(vn0, a21);
    p1 = Vector3::dot(vn1, a21);
    p2 = Vector3::dot(vn2, a21);
    r = e0 * std::abs(f1.y) + e1 * std::abs(f1.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }

    Vector3 a22;
    a22.x = -f2.y;
    a22.y = f2.x;
    a22.z = 0;

    p0 = Vector3::dot(vn0, a22);
    p1 = Vector3::dot(vn1, a22);
    p2 = Vector3::dot(vn2, a22);
    r = e0 * std::abs(f2.y) + e1 * std::abs(f2.x);
    if (std::max(-std::max(p0, std::max(p1, p2)), std::min(std::min(p0, p1), p2)) > r)
    {
        return false;
    }


    if (std::max(vn0.x, std::max(vn1.x, vn2.x)) < -e0 || std::min(vn0.x, std::min(vn1.x, vn2.x)) > e0)
    {
        return false;
    }

    if (std::max(vn0.y, std::max(vn1.y, vn2.y)) < -e1 || std::min(vn0.y, std::min(vn1.y, vn2.y)) > e1)
    {
        return false;
    }

    if (std::max(vn0.z, std::max(vn1.z, vn2.z)) < -e2 || std::min(vn0.z, std::min(vn1.z, vn2.z)) > e2)
    {
        return false;
    }
    return true;
}