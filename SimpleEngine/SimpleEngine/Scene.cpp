#include "Scene.h"

Scene::Scene(Camera camera) : camera(camera)
{
}

void Scene::addObj(std::string path)
{
	objParser::parseObj(triangles, vertex, textureCoord, path);
}

std::vector<std::vector<bool>> Scene::getFrame()
{
	return camera.draw(triangles);
}
