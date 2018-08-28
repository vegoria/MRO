#pragma once

enum ImageKind
{
    ORIGINAL,
    GAUSSIAN,
    GRADIENT,
    WATERSHED,
    MAX_IMAGE_TYPE
};

int readImageHeader(int& width, int& height, int& maxColor);
void readImageData(int width, int height, int maxColor, int headerPos, unsigned char **image);
void deallocateMemory(unsigned char** array);
void saveImage(unsigned char** image, int width, int height, ImageKind imageKind);