#include "Scene.h"
#include "BMPWriter.h"

Scene::Scene(Camera camera) : camera(camera)
{
}

void Scene::addObj(std::string objPath, std::string file_name)
{
	objParser::parseObj(triangles, trianglesTextureName,trianglesTexture, texture, objPath, file_name);
}

std::vector<std::vector<Pixel_triplet>> Scene::getFrame()
{
	std::vector<std::vector<std::pair<int, Vector3>>> vectorsUV = camera.draw(triangles);
	std::vector<std::vector<Pixel_triplet>> res(vectorsUV.size(), std::vector<Pixel_triplet>(vectorsUV[0].size(), Pixel_triplet(0, 0, 0)));
	for (size_t i = 0; i < vectorsUV.size(); i++)
	{
		for (size_t j = 0; j < vectorsUV[0].size(); j++)
		{
			if (vectorsUV[i][j].first != -1)
			{
				Vector2 P = trianglesTexture[vectorsUV[i][j].first].getVertex(0) * vectorsUV[i][j].second.x +
					trianglesTexture[vectorsUV[i][j].first].getVertex(1) * vectorsUV[i][j].second.y +
					trianglesTexture[vectorsUV[i][j].first].getVertex(2) * vectorsUV[i][j].second.z;


				P.x = P.x - floor(P.x);
				P.y = P.y - floor(P.y);


				res[i][j] = texture[trianglesTextureName[vectorsUV[i][j].first]][floor(P.y * (texture[trianglesTextureName[vectorsUV[i][j].first]].size() - 1))][floor(P.x * (texture[trianglesTextureName[vectorsUV[i][j].first]][0].size() - 1))];
			}
		}
	}
	return res;
}

Vector3 Scene::getCenter()
{
	Vector3 center(0, 0, 0);
	for (int i = 0; i < vertex.size(); i++)
	{
		center.x = center.x + vertex[i].x;
		center.y = center.y + vertex[i].y;
		center.z = center.z + vertex[i].z;
	}
	center.x = center.x / vertex.size();
	center.y = center.y / vertex.size();
	center.z = center.z / vertex.size();
	return center;
}
