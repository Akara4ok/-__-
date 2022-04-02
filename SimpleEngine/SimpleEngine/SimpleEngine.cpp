#include <iostream>
#include <ctime>
#include "Vector3.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "BMPWriter.h"
#include "objParser.h"

int main() {
	int start = clock();
	std::vector<Triangle> trs = objParser::parseObj("D:\\cow.obj");;
	Camera camera(1, 0.09, 0.16, 270, 480);
	Ray player(Vector3(-10, -10, 0), Vector3(1, 1, 0));
	camera.setScreen(player);
	auto res = camera.draw(trs);
	BMPWriter::writePicture(res, "D:\\bmp1.bmp");

	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}
