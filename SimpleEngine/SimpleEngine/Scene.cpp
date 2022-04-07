#include "Scene.h"
#include "BMPWriter.h"
#include <exception>

Scene::Scene(Camera camera, LightSource light) : camera(camera), lightSource(light)
{
}

void Scene::addObj(std::string objPath, std::string file_name)
{
	try
	{
		objParser::parseObj(triangles, trianglesTextureName, trianglesTexture, texture, objPath, file_name);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

std::vector<std::vector<Pixel_triplet>> Scene::getFrame()
{
	std::vector < std::vector<std::pair<std::pair<int, Vector3>, Vector3>>> vectorsUV = camera.draw(triangles);
	std::vector<std::vector<Vector3>> layers(vectorsUV.size(), std::vector<Vector3>(vectorsUV[0].size(), Vector3(0, 0, 0)));
	std::vector<std::vector<Pixel_triplet>> res(vectorsUV.size(), std::vector<Pixel_triplet>(vectorsUV[0].size(), Pixel_triplet(0, 0, 0)));

	Vector3 lightVector = Vector3(lightSource.color.redComponent / 255, lightSource.color.greenComponent / 255, lightSource.color.blueComponent / 255);
	for (size_t i = 0; i < vectorsUV.size(); i++)
	{
		for (size_t j = 0; j < vectorsUV[0].size(); j++)
		{
			if (vectorsUV[i][j].first.first != -1)
			{
				Vector2 P = trianglesTexture[vectorsUV[i][j].first.first].getVertex(0) * vectorsUV[i][j].second.x +
					trianglesTexture[vectorsUV[i][j].first.first].getVertex(1) * vectorsUV[i][j].second.y +
					trianglesTexture[vectorsUV[i][j].first.first].getVertex(2) * vectorsUV[i][j].second.z;

				P.x = P.x - floor(P.x);
				P.y = P.y - floor(P.y);

				auto a = Vector3(vectorsUV[i][j].first.second, lightSource.orig);

				Vector3 n = triangles[vectorsUV[i][j].first.first].getNormal();
				float cos = Vector3::getCos(n, Vector3(vectorsUV[i][j].first.second, lightSource.orig));
				if (cos * Vector3::getCos(n, Vector3(vectorsUV[i][j].first.second, camera.getOrig())) < 0)
					cos = 0.1;



				if (!texture[trianglesTextureName[vectorsUV[i][j].first.first]].empty())
				{
					Pixel_triplet textureColor = texture[trianglesTextureName[vectorsUV[i][j].first.first]][floor(P.y * (texture[trianglesTextureName[vectorsUV[i][j].first.first]].size() - 1))][floor(P.x * (texture[trianglesTextureName[vectorsUV[i][j].first.first]][0].size() - 1))];
					Vector3 textureVector = Vector3((float)textureColor.redComponent / 255, (float)textureColor.greenComponent / 255, (float)textureColor.blueComponent / 255);
					layers[i][j] = textureVector;
				}
				else
				{
					layers[i][j] = Vector3(1, 1, 1);
				}

				layers[i][j].x = layers[i][j].x * lightVector.x * cos;
				layers[i][j].y = layers[i][j].y * lightVector.y * cos;
				layers[i][j].z = layers[i][j].z * lightVector.z * cos;
			}
		}
	}

	for (size_t i = 0; i < vectorsUV.size(); i++)
	{
		for (size_t j = 0; j < vectorsUV[0].size(); j++)
		{
			res[i][j] = Pixel_triplet(layers[i][j].x * 255, layers[i][j].y * 255, layers[i][j].z * 255);
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
