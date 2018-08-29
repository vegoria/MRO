#pragma once

void erode(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
void dilatate(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
void makeDifferenceImage(unsigned char** inputImage, unsigned char** outputImage, int width, int height);