#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"
#include "LightSource.h"
#include "Box.h"

int main() {
	int start = clock();
	int end;
	Camera camera(0.08, 0.09, 0.16, 1080, 1920);
	Ray player(Vector3(0, 1, 0), Vector3(0, -1, 0));
	//Ray player(Vector3(3, 3, 4), Vector3(-3, -3, -4));
	LightSource light(Vector3(3, 3, 3), Pixel_triplet(255, 255, 255), 2, 0.1);
	std::vector<LightSource> lightSources;
	lightSources.push_back(light);
	camera.setScreen(player);
	Scene scene(camera, lightSources);
	end = clock();
	std::cout << "Scene created - " << end - start << "ms\n";
	scene.addObj("D:\\test", "cow.obj");
	end = clock();
	std::cout << "Object parsed - " << end - start << "ms\n";
	Pixel_triplet** res = scene.getFrame();
	end = clock();
	std::cout << "Got frame - " << end - start << "ms\n";
	BMPWriter::writePicture(res, camera.getPixelH(), camera.getPixelW(), "D:\\test\\bmp.bmp");
	end = clock();
	std::cout << "Wrote picture - " << end - start << "ms\n";
	end = clock();
	std::cout << "Total: " << end - start << "ms\n";

	return 0;
}


