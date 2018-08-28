#include "../include/gaussianFilter.hpp"
#include <iostream>
#include <cmath>
using namespace std;

GaussianFilter::GaussianFilter(double p_sigma):
    sigma(p_sigma)
{
    makeGaussianArray();
    printGaussianArray();
    countWeightSum();
}

void GaussianFilter::countWeightSum()
{
    weightSum = 0;
    for(int i=0; i< GAUSSIAN_ARRAY_SIZE; i++)
    {
        for(int j=0; j< GAUSSIAN_ARRAY_SIZE; j++)
            weightSum += gaussianValues[i][j];
    }
    cout << "[INF] Weight sum = " << weightSum << endl;
}

void GaussianFilter::makeGaussianArray()
{
    int middle = GAUSSIAN_ARRAY_SIZE/2;
    int maxValue = pow(2, middle+1);
    gaussianValues[middle][middle] = maxValue;
    for(int i=1; i<=middle; i++)
    {
        gaussianValues[middle-i][middle] = gaussianValues[middle-i+1][middle]/2;
        gaussianValues[middle+i][middle] = gaussianValues[middle+i-1][middle]/2;
    }

    for(int j=1; j<=middle; j++)
    {
        for(int i=0; i < GAUSSIAN_ARRAY_SIZE; i++)
        {
            gaussianValues[i][middle-j] = gaussianValues[i][middle-j+1]/2;
            if(gaussianValues[i][middle-j] == 0)
            {
                gaussianValues[i][middle-j] = 1;
            }
            gaussianValues[i][middle+j] = gaussianValues[i][middle+j-1]/2;
            if(gaussianValues[i][middle+j] == 0)
            {
                gaussianValues[i][middle+j] = 1;
            }
        }

    }
}

void GaussianFilter::printGaussianArray()
{
    cout << "[INF] Gaussian array:" << endl;
    for(int i=0; i< GAUSSIAN_ARRAY_SIZE; i++)
    {
        for(int j=0; j< GAUSSIAN_ARRAY_SIZE; j++)
            cout << " " << gaussianValues[i][j] << " ";
        cout << endl;
    }
}

void GaussianFilter::performGaussianBlur(unsigned char** inputImage, unsigned char** outputImage, int width, int height)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<height; j++)
            outputImage[i][j] = 0;
    }
    int middle = GAUSSIAN_ARRAY_SIZE/2;
    unsigned int pixelValue = 0;
    for(int i=middle; i<height-middle; i++)
    {
        pixelValue = 0;
        for(int j=middle; j<width-middle; j++)
        {
            for(int k=0; k<GAUSSIAN_ARRAY_SIZE; k++)
            {
                for(int l=0; l<GAUSSIAN_ARRAY_SIZE; l++)
                {
                    pixelValue += inputImage[i-middle+k][j-middle+l]*gaussianValues[k][l];
                }
                outputImage[i][j] = pixelValue/weightSum;
            }
        }
    }
}