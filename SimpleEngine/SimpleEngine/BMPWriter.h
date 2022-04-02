#pragma once
#include <iostream>
#include "BMPStruct.h"
#include <vector>

class BMPWriter
{
	BMP_head head;
	Pixel_triplet** pixels;
public:
	void writePicture(std::vector<std::vector<bool>> photo,std::string path);
};