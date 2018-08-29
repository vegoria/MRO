#include "../include/imageOperations.hpp"
#include "../include/imageManagment.hpp"
#include <iostream>

using namespace std;

#define NEIGHBOURHOOD 1

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
    cout << "[OK} Difference image crated" << endl;
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
