#pragma once

double erode(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
double dilatate(unsigned char** inputImage, int height, int width, unsigned char** outputImage);
double makeDifferenceImage(unsigned char** inputImage, unsigned char** outputImage, int width, int height);
double gaussianFilter(unsigned char** image, int width, int height);
double makeBright(unsigned char** image, int width, int height, int alpha);
void addImages(unsigned char** firstImage,  unsigned char** secondImage,  unsigned char** outputImage, int height, int width);
void negateImage(unsigned char** image, int height, int width);
double makeGaussianFilterSeveralTimes(unsigned char** image, int width, int height, int times);