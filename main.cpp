#include <iostream>
#include "include/imageManagment.hpp"
#include "include/imageOperations.hpp"
using namespace std;



int main()
{
    int height, width, maxColor;
    int headerPos = readImageHeader(width, height, maxColor);

    auto **inputImage = new unsigned char* [height];
    inputImage[0] = new unsigned char [height*width];
    for(int i = 1; i < height; i++)
    {
        inputImage[i] = inputImage[i-1] + width;
    }

    readImageData(width, height, maxColor, headerPos, inputImage);
    cout << "[INF] Image size are: " << height << " x " << width << endl;

    auto **differenceImage = new unsigned char* [height];
    differenceImage[0] = new unsigned char [height*width];
    for(int i = 1; i < height; i++)
    {
        differenceImage[i] = differenceImage[i-1] + width;
    }

    makeGaussianFilterSeveralTimes(inputImage, width, height, 6);
    saveImage(inputImage, width, height, FILTERED);
    makeDifferenceImage(inputImage, differenceImage, width, height);

    gaussianFilter(differenceImage, width, height);
    makeBright(differenceImage, width, height, 10);
//    addImages(differenceImage,  differenceImage,  differenceImage, height, width);
//    gaussianFilter(differenceImage, width, height);
//    negateImage(differenceImage, height, width);
//
//    dilatate(differenceImage, height, width, inputImage);
//    erode(differenceImage, height, width, inputImage);
    saveImage(differenceImage, width, height, WATERSHED);
    cout << "[INF] Difference Image dealocation: " << endl;
    deallocateMemory(differenceImage);
    cout << "[INF] Input Image dealocation: " << endl;
    deallocateMemory(inputImage);
    cout << "[OK] Program finished" << endl;
    return 0;
}