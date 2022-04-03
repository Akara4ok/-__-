#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"

int main() {
	int start = clock();
	int end;

	Camera camera(0.08, 0.09, 0.16, 1080, 1920);
	Ray player(Vector3(2, 3, 3), Vector3(-200, -300, -300));
	camera.setScreen(player);
	Scene scene(camera);
	end = clock();
	std::cout << "Scene created - " << end - start << "ms\n";
	scene.addObj("D:\\test4", "cow.obj");
	end = clock();
	std::cout << "Object parsed - " << end - start << "ms\n";
	auto res = scene.getFrame();
	end = clock();
	std::cout << "Got frame - " << end - start << "ms\n";
	BMPWriter::writePicture(res, "D:\\test4\\bmp.bmp");
	std::cout << "Wrote picture - " << "\n";
	end = clock();
	std::cout << "Total:" << end - start << "ms\n";
	return 0;
}


