#include <iostream>
#include <ctime>
#include "Vector3.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"

int main() {
	int start = clock();
	Triangle tr(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
	Camera camera(1, 0.1, 0.16, 10, 16);
	Ray player(Vector3(-10, -10, -10), Vector3(1, 1, 1) - Vector3(0, 0, 0));
	camera.setScreen(player);

	auto res = camera.draw(std::vector<Triangle>(1, tr));

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			if (res[i][j])
				std::cout << "@";
			else
				std::cout << ".";
		}
		std::cout << "\n";
	}
	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}
