#include "objParser.h"
#include "Vector3.h"
#include <fstream>

void objParser::parseObj(std::vector<Triangle>& triangles, std::vector<Vector3>& vertex, std::vector<TriangleUV>& trianglesTexture, std::string path)
{
    std::vector<Vector2> textureCoord;
    std::ifstream fin(path);
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
                if (next == s.npos)
                    next = s.find(" ", tprev);
                ntVertex.push_back(std::stoi(s.substr(tprev, next - prev)) - 1);

                if (i >= 2)
                {
                    triangles.push_back(Triangle(vertex[nVertex[0]], vertex[nVertex[i - 1]], vertex[nVertex[i]]));
                    trianglesTexture.push_back(TriangleUV(textureCoord[ntVertex[0]], textureCoord[ntVertex[i - 1]], textureCoord[ntVertex[i]]));
                }
                i++;
                next = s.find(" ", prev);
                prev = next + 1;
            }
        }
    }
}
