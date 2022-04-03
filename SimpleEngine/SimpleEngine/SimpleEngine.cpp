#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"

int main() {
	int start = clock();

	Camera camera(0.08, 0.09, 0.16, 1080, 1920);
	Ray player(Vector3(200, 300, 300), Vector3(-200, -300, -300));
	camera.setScreen(player);
	Scene scene(camera);
	scene.addObj("D:\\test2", "newscene.obj");
	auto res = scene.getFrame();
	BMPWriter::writePicture(res, "D:\\test\\bmp.bmp");

	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}


