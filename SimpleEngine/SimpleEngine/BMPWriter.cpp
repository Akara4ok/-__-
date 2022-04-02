#include "BMPWriter.h"
#include <fstream>

void  BMPWriter::writePicture(std::vector<std::vector<bool>> photo, std::string file_name)
{
    std::ofstream fout;
    fout.open(file_name, std::ios::binary);


    int width = photo[0].size();
    int height = photo.size();
    int size = width * height + 54;
    head.id[0] = 'B';
    head.id[1] = 'M';
    head.fileSize = size;
    head.reserved[0] = 0;
    head.reserved[1] = 0;
    head.headerSize = 54;
    head.infoSize = 40;
    head.width = width;
    head.height = height;
    head.biplanes = 1;
    head.bitsPixel = 24;
    head.biCompression = 0;
    head.biSizeImage = size - 54;
    head.biXPelsPerMeter = 2834;
    head.biXPelsPerMeter = 2834;
    head.biClrUsed = 0;
    head.biClrImportant = 0;
    fout.write((char*)&head, sizeof(BMP_head));

    int number_insignificant = 4 - (head.width * 3 % 4);
    if (number_insignificant == 4)
        number_insignificant = 0;

    uint8_t insignificant = 0;
    pixels = new Pixel_triplet * [height];
    for (int i = 0; i < height; i++)
    {
        pixels[i] = new Pixel_triplet[width];
        for (int j = 0; j < width; j++)
        {
            if (photo[i][j])
            {
                pixels[i][j].redComponent = 255;
                pixels[i][j].blueComponent = 255;
                pixels[i][j].greenComponent = 255;
            }
            else
            {
                pixels[i][j].redComponent = 0;
                pixels[i][j].blueComponent = 0;
                pixels[i][j].greenComponent = 0;
            }
        }
    }

    for (int i = 0; i < head.height; i++)
    {
        for (int j = 0; j < head.width; j++)
        {
            fout.write((char*)&pixels[i][j], sizeof(Pixel_triplet));
        }

        for (int k = 0; k < number_insignificant; k++)
        {
            fout.write((char*)&insignificant, sizeof(int8_t));
        }
    }

    fout.close();
}