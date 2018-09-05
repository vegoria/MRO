#pragma once


#include <string>

enum ImageKind
{
    ORIGINAL,
    ERODED,
    DILATATED,
    DIFFERENCE_IMG,
    WATERSHED,
    FILTERED,
    MAX_IMAGE_TYPE
};

int readImageHeader(int& width, int& height, int& maxColor);
void readImageData(int width, int height, int maxColor, int headerPos, unsigned char **image);
void deallocateMemory(unsigned char** array);
void saveImage(unsigned char** image, int width, int height, ImageKind imageKind);
void saveImageWithPath(unsigned char** image, int width, int height, std::string path);
