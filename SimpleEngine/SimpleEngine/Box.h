#pragma once
#include "Vector3.h"

struct Box
{
	Vector3 min;
	Vector3 max;
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
};

