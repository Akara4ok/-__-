#include <iostream>
#include <ctime>
#include "Vector3.h"
#include "Camera.h"
#include "Ray.h"

int main() {
	int start = clock();
	Ray player(Vector3(1, 0, 0), Vector3(1, 1, 1));
	Camera camera;
	camera.setScreen(player);
	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}
