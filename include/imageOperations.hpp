#pragma once

void erode(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
void dilatate(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
void makeDifferenceImage(unsigned char** inputImage, unsigned char** outputImage, int width, int height);
void gaussianFilter(unsigned char** image, int width, int height);
void makeBright(unsigned char** image, int width, int height, int alpha);
void addImages(unsigned char** firstImage,  unsigned char** secondImage,  unsigned char** outputImage, int height, int width);
void negateImage(unsigned char** image, int height, int width);
void makeGaussianFilterSeveralTimes(unsigned char** image, int width, int height, int times);