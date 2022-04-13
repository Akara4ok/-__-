#pragma once
#include "Node.h"
#include "Ray.h"

class OctTree
{
	int count_tr = 10;
	float min_size = 0.001;
	Node* root;
	std::vector<Triangle> triangle;
public:
	OctTree() {};
	OctTree(Box box, std::vector<Triangle>& tr);
	void divCube(Node*& root);
	bool findMinIntersection(Ray r, int& minTriangle, float& minDist, float& u, float& v);
	void recursivelyFindMinIntersection(Node* root, Ray r, int& minTriangle, float& minDist, float& u, float& v);
};

