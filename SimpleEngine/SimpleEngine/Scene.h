#pragma once
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Triangle.h"
#include "objParser.h"
#include "Camera.h"

class Scene
{
    std::vector<Triangle> triangles;
    std::vector<Vector3> vertex;
    std::vector<Vector2> textureCoord;
    Camera camera;
public:
    Scene(Camera camera);
    void addObj(std::string path);
    std::vector<std::vector<bool>> getFrame();
};

