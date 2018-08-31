#include "../include/imageOperations.hpp"
#include "../include/imageManagment.hpp"
#include <iostream>

using namespace std;

#define NEIGHBOURHOOD 1

void makeBright(unsigned char** image, int width, int height, int alpha)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j] *= alpha;
            if(image[i][j]>255) image[i][j]=255;
        }
    }
    cout << "[OK] Image is brighter " << alpha << " times" << endl;
}

void gaussianFilter(unsigned char** image,
                    int width,
                    int height)
{
    int gaussianFilter[5][5] = {{1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    int weight = 0;
    int sum = 273;
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
    cout << "[OK] Gaussian filter performed" << endl;
}

void makeDifferencedImage(unsigned char** erodedImage,
                          unsigned char** dilatatedImage,
                          int width,
                          int height,
                          unsigned char** destinyImage)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
            destinyImage[i][j] = dilatatedImage[i][j]-erodedImage[i][j];
    }
    cout << "[OK] Difference image crated" << endl;
}

void erode(unsigned char** inputImage, int height, int width, unsigned char** outputImage)
{
    int minimalValue;
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
    cout << "[OK] Eroded image created" << endl;
}

void dilatate(unsigned char** inputImage, int height, int width, unsigned char** outputImage)
{
    int maximumValue = 0;
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
    cout << "[OK] Dilatated image created" << endl;
}




void makeDifferenceImage(unsigned char** inputImage, unsigned char** outputImage, int width, int height) {
    auto **erodedImage = new unsigned char *[height];
    erodedImage[0] = new unsigned char[height * width];
    for (int i = 1; i < height; i++) {
        erodedImage[i] = erodedImage[i - 1] + width;
    }
    erode(inputImage, height, width, erodedImage);
    saveImage(erodedImage, width, height, ERODED);

    auto **dilatatedImage = new unsigned char *[height];
    dilatatedImage[0] = new unsigned char[height * width];
    for (int i = 1; i < height; i++) {
        dilatatedImage[i] = dilatatedImage[i - 1] + width;
    }
    dilatate(inputImage, height, width, dilatatedImage);
    saveImage(dilatatedImage, width, height, DILATATED);

    makeDifferencedImage(erodedImage, dilatatedImage, width, height, outputImage);
    saveImage(outputImage, width, height, DIFFERENCE);
    deallocateMemory(erodedImage);
    deallocateMemory(dilatatedImage);

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

void makeGaussianFilterSeveralTimes(unsigned char** image, int width, int height, int times)
{
    cout << "[INF] Performing gaussian filter " << times << "times" << endl;
    for(int i=0; i<times; i++)
    {
        gaussianFilter(image, width, height);
    }
    cout << "[OK] Multiple gaussian filters done" << endl;
}
