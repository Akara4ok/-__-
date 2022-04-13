#pragma once
#include <vector>
#include <map>
#include "Vector2.h"
#include "Vector3.h"
#include "Triangle.h"
#include "TriangleUV.h"
#include "objParser.h"
#include "Camera.h"
#include "BMPStruct.h"
#include "LightSource.h"
#include "Box.h"
#include "OctTree.h"

class Scene
{
    std::vector<Vector3> vertex;
    std::vector<Triangle> triangles;
    std::vector<std::string> trianglesTextureName;
    std::vector<TriangleUV> trianglesTexture;
    std::map<std::string, std::vector<std::vector<Pixel_triplet>>> texture;
    std::vector<LightSource> lightSources;
    Camera camera;
    Box boundingBox = Box(Vector3(-10, -10, -10), Vector3(10, 10, 10));
    OctTree octTree;
public:
    Scene(Camera camera, std::vector<LightSource> light);
    void addObj(std::string objPath, std::string file_name);
    std::vector<std::vector<Pixel_triplet>> getFrame();
    Vector3 getCenter();
};

