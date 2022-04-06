#include "objParser.h"
#include "Vector3.h"
#include <fstream>
#include <map>
#include "BMPWriter.h"

void objParser::parseObj(std::vector<Triangle>& triangles, std::vector<std::string>& trianglesTextureName, std::vector<TriangleUV>& trianglesTexture, std::map<std::string, std::vector<std::vector<Pixel_triplet>>>& textures, std::string path, std::string file_name)
{
    std::vector<Vector3> vertex;
    std::vector<Vector2> textureCoord;
    std::ifstream fin(path + "\\" + file_name);
    std::ifstream finMtl;
    std::string lastTexture;

    if (!fin.is_open())
        throw std::runtime_error("Error! Unable to open the obj file.\n");

    while (!fin.eof())
    {
        std::string s;
        std::getline(fin, s);

        size_t next, prev;
        if (s[0] == 'v' && s[1] == ' ')
        {
            float x, y, z;

            prev = 2;
            next = s.find(" ", prev);
            x = std::stof(s.substr(prev, next - prev));
            prev = next + 1;

            next = s.find(" ", prev);
            y = std::stof(s.substr(prev, next - prev));
            prev = next + 1;

            next = s.find(" ", prev);
            z = std::stof(s.substr(prev, next - prev));
            prev = next + 1;

            vertex.push_back(Vector3(x, y, z));
        }
        if (s[0] == 'v' && s[1] == 't' && s[2] == ' ')
        {
            float x, y, z;

            prev = 3;
            next = s.find(" ", prev);
            x = std::stof(s.substr(prev, next - prev));
            prev = next + 1;

            next = s.find(" ", prev);
            y = std::stof(s.substr(prev, next - prev));
            prev = next + 1;

            textureCoord.push_back(Vector2(x, y));
        }
        if (s[0] == 'f' && s[1] == ' ')
        {
            prev = 2;
            next = prev;
            bool isTextures = true;
            int i = 0;
            std::vector<int> nVertex;
            std::vector<int> ntVertex;
            while (next != s.npos)
            {
                if (prev == s.length())
                    break;
                next = s.find("/", prev);
                if (next == s.npos)
                    next = s.find(" ", prev);
                nVertex.push_back(std::stoi(s.substr(prev, next - prev)) - 1);
                
                
                int tprev = next + 1;
                next = s.find("/", tprev);
                if (next == s.npos || next == tprev)
                {
                    next = s.find(" ", prev);
                    isTextures = false;
                }
                else
                {
                    ntVertex.push_back(std::stoi(s.substr(tprev, next - tprev)) - 1);
                }

                if (i >= 2)
                {
                    triangles.push_back(Triangle(vertex[nVertex[0]], vertex[nVertex[i - 1]], vertex[nVertex[i]]));
                    if (isTextures)
                        trianglesTexture.push_back(TriangleUV(textureCoord[ntVertex[0]], textureCoord[ntVertex[i - 1]], textureCoord[ntVertex[i]]));
                    else
                        trianglesTexture.push_back(TriangleUV(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0)));
                    trianglesTextureName.push_back(lastTexture);
                }
                i++;
                next = s.find(" ", prev);
                prev = next + 1;
            }
        }
        if (s.find("mtllib") != s.npos)
        {
            prev = s.find(" ") + 1;
            next = s.find(" ", prev);
            std::string mtlName = s.substr(prev, next - prev);
            finMtl.open(path + "\\" + mtlName);
            if (!finMtl.is_open())
                continue;
            std::string lastNewMtl;
            std::string lastPath;
            while (!finMtl.eof())
            {
                std::string s;
                std::getline(finMtl, s);
                if (s.find("newmtl ") != s.npos)
                {
                    prev = s.find(" ") + 1;
                    next = s.find(" ", prev);
                    lastNewMtl = s.substr(prev, next - prev);
                }
                if (s.find("map_Kd ") != s.npos)
                {
                    int pos = s.find("map_Kd ");
                    prev = pos + 7;
                    while (s[prev] == ' ')
                    {
                        prev++;
                    }
                    next = s.find(" ", prev);
                    lastPath = s.substr(prev, next - prev);
                    if (!((lastPath[0] == 'D' || lastPath[0] == 'D') && lastPath[1] == ':'))
                        lastPath = path + "\\" + lastPath;
                    try
                    {
                        std::vector<std::vector<Pixel_triplet>> photo = BMPWriter::readPicture(lastPath);
                        textures[lastNewMtl] = photo;
                    }
                    catch (std::runtime_error e)
                    {
                        std::cout << e.what();
                        textures[lastNewMtl] = std::vector<std::vector<Pixel_triplet>>();
                    }
                }
            }
            finMtl.close();
        }
        if (s.find("usemtl") != s.npos)
        {
            prev = s.find(" ") + 1;
            next = s.find(" ", prev);
            lastTexture = s.substr(prev, next - prev);
        }
    }
}
