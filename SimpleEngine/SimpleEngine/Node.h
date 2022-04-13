#pragma once
#include "Box.h"
#include "Triangle.h"
#include <vector>

struct Node
{
	Box box;
	std::vector<int> nTringle;
	Node* ptr_node[8];
	Node() {};
	Node(Box region, std::vector<int> tr) : box(region), nTringle(tr)
	{
		for (int i = 0; i < 8; i++)
			ptr_node[i] = nullptr;
	}
};
