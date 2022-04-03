#pragma once
#include <iostream>

#pragma pack(push, 1)
struct BMP_head
{
	int8_t  id[2];
	int32_t fileSize;
	int16_t reserved[2];
	int32_t headerSize;
	int32_t infoSize;
	int32_t width;
	int32_t height;
	int16_t biplanes;
	int16_t bitsPixel;
	int32_t biCompression;
	int32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	int32_t biClrUsed;
	int32_t biClrImportant;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Pixel_triplet
{
	uint8_t blueComponent;
	uint8_t greenComponent;
	uint8_t redComponent;
	//uint8_t alpa_mask;
	Pixel_triplet() {}
	Pixel_triplet(uint8_t r, uint8_t g, uint8_t b) : redComponent(r), greenComponent(g), blueComponent(b) {}
};
#pragma pack(pop)