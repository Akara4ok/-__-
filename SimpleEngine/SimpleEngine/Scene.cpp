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

	octTree = OctTree(boundingBox, triangles);
	int k;
}

Pixel_triplet** Scene::getFrame()
{
	int pixelH = camera.getPixelH();
	int pixelW = camera.getPixelW();

	int** nTriangle = new int* [pixelH];
	Vector3** PointTriangleIntersection = new Vector3 * [pixelH];
	Vector3** UVCoord = new Vector3 * [pixelH];
	for (size_t i = 0; i < pixelH; i++)
	{
		nTriangle[i] = new int[pixelW];
		for (size_t j = 0; j < pixelW; j++)
		{
			nTriangle[i][j] = -1;
		}
		PointTriangleIntersection[i] = new Vector3[pixelW];
		UVCoord[i] = new Vector3[pixelW];
	}

	camera.draw(octTree, triangles, nTriangle, PointTriangleIntersection, UVCoord);
	

	Vector3*** layers = new Vector3 * *[lightSources.size()];
	for (size_t k = 0; k < lightSources.size(); k++)
	{
		layers[k] = new Vector3 * [pixelH];
		for (size_t i = 0; i < pixelH; i++)
		{
			layers[k][i] = new Vector3[pixelW];
			for (size_t j = 0; j < pixelW; j++)
			{
				layers[k][i][j] = Vector3(0, 0, 0);
			}
		}
	}


	Pixel_triplet** res = new Pixel_triplet * [pixelH];
	for (size_t i = 0; i < pixelH; i++)
	{
		res[i] = new Pixel_triplet[pixelW];
		for (size_t j = 0; j < pixelW; j++)
		{
			res[i][j] = Pixel_triplet(0, 0, 0);
		}
	}


	for (size_t k = 0; k < lightSources.size(); k++)
	{
		Vector3 lightVector = Vector3(lightSources[k].color.redComponent / 255, lightSources[k].color.greenComponent / 255, lightSources[k].color.blueComponent / 255);
		for (size_t i = 0; i < pixelH; i++)
		{
			for (size_t j = 0; j < pixelW; j++)
			{
				if (nTriangle[i][j] != -1)
				{
					Vector2 P = trianglesTexture[nTriangle[i][j]].getVertex(0) * UVCoord[i][j].x +
						trianglesTexture[nTriangle[i][j]].getVertex(1) * UVCoord[i][j].y +
						trianglesTexture[nTriangle[i][j]].getVertex(2) * UVCoord[i][j].z;

					P.x = P.x - floor(P.x);
					P.y = P.y - floor(P.y);

					Vector3 n = triangles[nTriangle[i][j]].getNormal();
					float cos = Vector3::getCos(n, Vector3(PointTriangleIntersection[i][j], lightSources[k].orig));
					if (cos * Vector3::getCos(n, Vector3(PointTriangleIntersection[i][j], camera.getOrig())) < 0)
						cos = 0.1;



					if (!texture[trianglesTextureName[nTriangle[i][j]]].empty())
					{
						Pixel_triplet textureColor = texture[trianglesTextureName[nTriangle[i][j]]][floor(P.y * (texture[trianglesTextureName[nTriangle[i][j]]].size() - 1))][floor(P.x * (texture[trianglesTextureName[nTriangle[i][j]]][0].size() - 1))];
						Vector3 textureVector = Vector3((float)textureColor.redComponent / 255, (float)textureColor.greenComponent / 255, (float)textureColor.blueComponent / 255);
						layers[k][i][j] = textureVector;
					}
					else
					{
						layers[k][i][j] = Vector3(1, 1, 1);
					}

					float a = pow(2, Vector3(PointTriangleIntersection[i][j], lightSources[k].orig).absValue());


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
						layers[k][i][j].x = std::min(layers[k][i][j].x * lightVector.x * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.x);
						layers[k][i][j].y = std::min(layers[k][i][j].y * lightVector.y * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.y);
						layers[k][i][j].z = std::min(layers[k][i][j].z * lightVector.z * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)layers[k][i][j].x * lightVector.z);
						break;
					case 3:
						layers[k][i][j].x = std::min(layers[k][i][j].x * lightVector.x * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)1);
						layers[k][i][j].y = std::min(layers[k][i][j].y * lightVector.y * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)1);
						layers[k][i][j].z = std::min(layers[k][i][j].z * lightVector.z * cos / (lightSources[k].diffCoef * pow(2, Vector3(PointTriangleIntersection[i][j], camera.getOrig()).absValue())), (double)1);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < pixelH; i++)
	{
		for (size_t j = 0; j < pixelW; j++)
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

	for (size_t i = 0; i < pixelH; i++)
	{
		delete[] nTriangle[i];
		delete[] PointTriangleIntersection[i];
		delete[] UVCoord[i];
	}

	for (size_t k = 0; k < lightSources.size(); k++)
	{
		for (size_t i = 0; i < pixelH; i++)
		{
			delete[] layers[k][i];
		}
		delete[] layers[k];
	}

	delete[] nTriangle;
	delete[] PointTriangleIntersection;
	delete[] layers;
	delete[] UVCoord;

	return res;
}

void Scene::setScreen(Ray playerView)
{
	camera.setScreen(playerView);
}
