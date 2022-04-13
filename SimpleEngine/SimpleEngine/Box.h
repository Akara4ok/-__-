#pragma once
#include "Vector3.h"

class Box
{
	Vector3 min;
	Vector3 max;
public:
	Box() {};
	Box(Vector3 v1, Vector3 v2) 
	{
		if (v1.z < v2.z)
		{
			min = v1;
			max = v2;
		}
		else
		{
			min = v2;
			max = v1;
		}
	}
	Vector3 getMin() 
	{
		return min;
	};
	Vector3 getMax()
	{
		return max;
	};
};

