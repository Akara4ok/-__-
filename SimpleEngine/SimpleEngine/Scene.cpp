#include "Scene.h"
#include "BMPWriter.h"
#include <exception>
#include <math.h>
#include <iostream>

Scene::Scene(Camera camera, std::vector<LightSource> light) : camera(camera), lightSources(light)
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
	std::vector<std::vector<std::vector<Vector3>>> layers(lightSources.size(), std::vector<std::vector<Vector3>> (vectorsUV.size(), std::vector<Vector3>(vectorsUV[0].size(), Vector3(0, 0, 0))));
	std::vector<std::vector<Pixel_triplet>> res(vectorsUV.size(), std::vector<Pixel_triplet>(vectorsUV[0].size(), Pixel_triplet(0, 0, 0)));


	for (size_t k = 0; k < lightSources.size(); k++)
	{
		Vector3 lightVector = Vector3(lightSources[k].color.redComponent / 255, lightSources[k].color.greenComponent / 255, lightSources[k].color.blueComponent / 255);
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

					Vector3 n = triangles[vectorsUV[i][j].first.first].getNormal();
					float cos = Vector3::getCos(n, Vector3(vectorsUV[i][j].first.second, lightSources[k].orig));
					if (cos * Vector3::getCos(n, Vector3(vectorsUV[i][j].first.second, camera.getOrig())) < 0)
						cos = 0.1;



					if (!texture[trianglesTextureName[vectorsUV[i][j].first.first]].empty())
					{
						Pixel_triplet textureColor = texture[trianglesTextureName[vectorsUV[i][j].first.first]][floor(P.y * (texture[trianglesTextureName[vectorsUV[i][j].first.first]].size() - 1))][floor(P.x * (texture[trianglesTextureName[vectorsUV[i][j].first.first]][0].size() - 1))];
						Vector3 textureVector = Vector3((float)textureColor.redComponent / 255, (float)textureColor.greenComponent / 255, (float)textureColor.blueComponent / 255);
						layers[k][i][j] = textureVector;
					}
					else
					{
						layers[k][i][j] = Vector3(1, 1, 1);
					}

					float a = pow(2, Vector3(vectorsUV[i][j].first.second, lightSources[k].orig).absValue());


					switch (lightSources[k].diffMode)
					{
					case 0:
						layers[k][i][j].x = layers[k][i][j].x * lightVector.x;
						layers[k][i][j].y = layers[k][i][j].y * lightVector.y;
						layers[k][i][j].z = layers[k][i][j].z * lightVector.z;
						break;
					case 1:
						layers[k][i][j].x = layers[k][i][j].x * lightVector.x * cos;
						layers[k][i][j].y = layers[k][i][j].y * lightVector.y * cos;
						layers[k][i][j].z = layers[k][i][j].z * lightVector.z * cos;
						break;
					case 2:
						layers[k][i][j].x = std::min(layers[k][i][j].x * lightVector.x * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.x);
						layers[k][i][j].y = std::min(layers[k][i][j].y * lightVector.y * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.y);
						layers[k][i][j].z = std::min(layers[k][i][j].z * lightVector.z * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.z);
						break;
					case 3:
						layers[k][i][j].x = std::min(layers[k][i][j].x * lightVector.x * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)1);
						layers[k][i][j].y = std::min(layers[k][i][j].y * lightVector.y * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)1);
						layers[k][i][j].z = std::min(layers[k][i][j].z * lightVector.z * cos / (lightSources[k].diffCoef * pow(2, Vector3(vectorsUV[i][j].first.second, camera.getOrig()).absValue())), (double)1);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < vectorsUV.size(); i++)
	{
		for (size_t j = 0; j < vectorsUV[0].size(); j++)
		{
			//res[i][j] = Pixel_triplet(layers[i][j].x * 255, layers[i][j].y * 255, layers[i][j].z * 255);
			for (size_t k = 0; k < lightSources.size(); k++)
			{
				res[i][j].redComponent = std::max((int) res[i][j].redComponent, (int) (layers[k][i][j].x * 255));
				res[i][j].greenComponent = std::max((int)res[i][j].greenComponent, (int) (layers[k][i][j].y * 255));
				res[i][j].blueComponent = std::max((int)res[i][j].blueComponent, (int) (layers[k][i][j].z * 255));
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
