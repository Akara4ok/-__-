#pragma once
#include <iostream>
#include "BMPStruct.h"
#include <vector>

class BMPWriter
{
public:
	static void writePicture(std::vector<std::vector<bool>> photo,std::string path);
};