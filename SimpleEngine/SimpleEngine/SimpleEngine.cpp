#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"
#include "LightSource.h"

int main() {
	int start = clock();
	int end;

	Camera camera(1, 0.16, 0.09, 192, 108);
	Ray player(Vector3(-1, -10, 0), Vector3(1, 10, 0));
	LightSource light(Vector3(-1, -1, -1), Pixel_triplet(255, 255, 255));
	camera.setScreen(player);
	Scene scene(camera, light);
	end = clock();
	std::cout << "Scene created - " << end - start << "ms\n";
	scene.addObj("D:\\test", "cow.obj");
	end = clock();
	std::cout << "Object parsed - " << end - start << "ms\n";
	auto res = scene.getFrame();
	end = clock();
	std::cout << "Got frame - " << end - start << "ms\n";
	BMPWriter::writePicture(res, "D:\\test\\bmp.bmp");
	end = clock();
	std::cout << "Wrote picture - " << end - start << "ms\n";
	end = clock();
	std::cout << "Total: " << end - start << "ms\n";
	return 0;
}


