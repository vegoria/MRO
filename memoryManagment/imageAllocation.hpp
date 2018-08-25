#pragma once

int readImageHeader(int& width, int& height, int& maxColor);
void readImageData(int width, int height, int maxColor, int headerPos, unsigned char **image);
void deallocateMemory(unsigned char** array);