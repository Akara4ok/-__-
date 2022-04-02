#include <iostream>
#include <ctime>
#include "BMPWriter.h"
#include "Scene.h"

int main() {
	int start = clock();

	Camera camera(0.01, 0.09, 0.16, 270, 480);
	Ray player(Vector3(0, -150, 0), Vector3(0, 1, 0));
	camera.setScreen(player);
	Scene scene(camera);
	scene.addObj("D:\\test\\newscene.obj");
	auto res = scene.getFrame();
	BMPWriter::writePicture(res, "D:\\test\\bmp1.bmp");

	int end = clock();
	std::cout << end - start << "ms\n";
	return 0;
}


