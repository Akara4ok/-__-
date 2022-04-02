#pragma once
#include <iostream>
#include "BMPStruct.h"
#include <vector>

class BMPWriter
{
public:
	static std::vector<std::vector<Pixel_triplet>> readPicture(std::string path);
	static void writePicture(std::vector<std::vector<Pixel_triplet>> photo, std::string path);
	static void writePicture(std::vector<std::vector<bool>> photo,std::string path);
};