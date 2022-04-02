#include <iostream>
#include <ctime>
#include "Vector3.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "BMPWriter.h"

int main() {
	int start = clock();
	Triangle tr1(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
	Triangle tr2(Vector3(0, 1, 0), Vector3(0, 0.5, 0.5), Vector3(2, 2, 0));
	std::vector<Triangle> trs;
	trs.push_back(tr1);
	trs.push_back(tr2);
	Camera camera(1, 0.1, 0.16, 1000, 1600);
	Ray player(Vector3(-25, -25, -25), Vector3(1, 1, 1));
	camera.setScreen(player);
	auto res = camera.draw(trs);
	BMPWriter bmp;
	bmp.writePicture(res, "D:\\bmp1.bmp");
	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}
