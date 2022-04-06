#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"
#include "LightSource.h"

int main() {
	int start = clock();
	int end;

	Camera camera(0.08, 0.09, 0.16, 1080, 1920);
	Ray player(Vector3(300, 300, 300), Vector3(-300, -300, -300));
	LightSource light(Vector3(500, 300, 300), Pixel_triplet(255, 255, 255));
	camera.setScreen(player);
	Scene scene(camera, light);
	end = clock();
	std::cout << "Scene created - " << end - start << "ms\n";
	scene.addObj("D:\\test", "newscene.obj");
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


