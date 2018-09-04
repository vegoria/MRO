#include "../include/imageOperations.hpp"
#include "../include/imageManagment.hpp"
#include <iostream>
#include "../tgaSrc/Ttiming.h"

using namespace std;

#define NEIGHBOURHOOD 1

double makeBright(unsigned char** image, int width, int height, int alpha)
{
    cout << "[INF] Make image " << alpha << " times brighter... ";
    TTiming tt;
    tt.Begin();
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j] *= alpha;
            if(image[i][j]>255) image[i][j]=255;
        }
    }
    double elapsedTime = tt.End();
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}

double gaussianFilter(unsigned char** image,
                    int width,
                    int height)
{
    TTiming tt;
    int gaussianFilter[5][5] = {{1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    int weight = 0;
    int sum = 273;
    tt.Begin();
    for(int i=2; i<height-2; i++)
    {
        for(int j=2; j<width-2; j++)
        {
            weight = 0;
            for(int k=-2; k<3; k++)
            {
                for(int l=-2; l<3; l++)
                {
                    weight += image[i+k][j+l]*gaussianFilter[k+2][l+2];
                }
            }
            image[i][j] = weight/sum;
        }
    }
    double elapsedTime = tt.End();
    return elapsedTime;
}

double makeDifferencedImage(unsigned char** erodedImage,
                          unsigned char** dilatatedImage,
                          int width,
                          int height,
                          unsigned char** destinyImage)
{
    cout << "[INF] Making difference image... ";
    TTiming tt;
    tt.Begin();
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
            destinyImage[i][j] = dilatatedImage[i][j]-erodedImage[i][j];
    }
    double elapsedTime = tt.End();
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}

double erode(unsigned char** inputImage, int height, int width, unsigned char** outputImage)
{
    cout << "[INF] Making eroded image... ";
    int minimalValue;
    TTiming tt;
    tt.Begin();
    for(int i=NEIGHBOURHOOD; i<height-NEIGHBOURHOOD-1; i++)
    {
        for(int j=NEIGHBOURHOOD; j<width-NEIGHBOURHOOD-1; j++){
            minimalValue = 255;
            for(int k=i-NEIGHBOURHOOD; k<i+NEIGHBOURHOOD+1; k++){
                for(int l=j-NEIGHBOURHOOD; l<j+NEIGHBOURHOOD+1; l++){
                    if(inputImage[k][l] < minimalValue)
                    {
                        minimalValue = inputImage[k][l];
                    }
                }

            }
            outputImage[i][j] = minimalValue;
        }
    }
    double elapsedTime = tt.End();
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}

double dilatate(unsigned char** inputImage, int height, int width, unsigned char** outputImage)
{
    cout << "[INF] Making dilatated image... ";
    int maximumValue = 0;
    TTiming tt;
    tt.Begin();
    for(int i=NEIGHBOURHOOD; i<height-NEIGHBOURHOOD-1; i++)
    {
        for(int j=NEIGHBOURHOOD; j<width-NEIGHBOURHOOD-1; j++){
            maximumValue = 0;
            for(int k=i-NEIGHBOURHOOD; k<i+NEIGHBOURHOOD+1; k++){
                for(int l=j-NEIGHBOURHOOD; l<j+NEIGHBOURHOOD+1; l++){
                    if(inputImage[k][l] > maximumValue)
                    {
                        maximumValue = inputImage[k][l];
                    }
                }
            }
            outputImage[i][j] = maximumValue;
        }
    }
    double elapsedTime = tt.End();
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}

double makeDifferenceImage(unsigned char** inputImage, unsigned char** outputImage, int width, int height) {
    double elapsedTime = 0.0;
    auto **erodedImage = new unsigned char *[height];
    erodedImage[0] = new unsigned char[height * width];
    for (int i = 1; i < height; i++) {
        erodedImage[i] = erodedImage[i - 1] + width;
    }
    elapsedTime += erode(inputImage, height, width, erodedImage);
    saveImage(erodedImage, width, height, ERODED);

    auto **dilatatedImage = new unsigned char *[height];
    dilatatedImage[0] = new unsigned char[height * width];
    for (int i = 1; i < height; i++) {
        dilatatedImage[i] = dilatatedImage[i - 1] + width;
    }
    elapsedTime += dilatate(inputImage, height, width, dilatatedImage);
    saveImage(dilatatedImage, width, height, DILATATED);

    elapsedTime += makeDifferencedImage(erodedImage, dilatatedImage, width, height, outputImage);
    saveImage(outputImage, width, height, DIFFERENCE_IMG);
    deallocateMemory(erodedImage);
    deallocateMemory(dilatatedImage);
    return elapsedTime;
}

void addImages(unsigned char** firstImage,  unsigned char** secondImage,  unsigned char** outputImage, int height, int width)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            outputImage[i][j] = firstImage[i][j]+secondImage[i][j];
            if(outputImage[i][j]>255) outputImage[i][j]=255;
        }
    }
    cout << "[OK] Images added" << endl;
}

void negateImage(unsigned char** image, int height, int width)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j] = 255-image[i][j];
        }
    }
    cout << "[OK] Images negated" << endl;
}

double makeGaussianFilterSeveralTimes(unsigned char** image, int width, int height, int times)
{
    cout << "[INF] Performing gaussian filter " << times << " times... ";
    double elapsedTime = 0.0;
    for(int i=0; i<times; i++)
    {
        elapsedTime += gaussianFilter(image, width, height);
    }
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}
