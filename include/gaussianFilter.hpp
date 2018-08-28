#pragma once
#define GAUSSIAN_ARRAY_SIZE 5
class GaussianFilter
{
public:
    explicit GaussianFilter(double p_sigma);
    void performGaussianBlur(unsigned char** inputImage, unsigned char** outputImage, int width, int height);

private:
    void printGaussianArray();
    void makeGaussianArray();
    void countWeightSum();

    int gaussianValues[GAUSSIAN_ARRAY_SIZE][GAUSSIAN_ARRAY_SIZE];
    unsigned int weightSum;
    double sigma;
};