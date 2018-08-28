#include <iostream>
#include "include/imageManagment.hpp"
#include "include/gaussianFilter.hpp"
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

    auto **gaussianImage = new unsigned char* [height];
    gaussianImage[0] = new unsigned char [height*width];
    for(int i = 1; i < height; i++)
    {
        gaussianImage[i] = gaussianImage[i-1] + width;
    }

    //JEST ŹLE TRZEBA ODKRYĆ JAK DOKŁADNIE ZROBIĆ TEN FILTR
    auto* gaussianFilter = new GaussianFilter(1.0);
    gaussianFilter->performGaussianBlur(inputImage, gaussianImage, width, height);
    delete gaussianFilter;
    cout << "[INF] Gaussian Image save: ";
    saveImage(gaussianImage, width, height, GAUSSIAN);

    cout << "[INF] Gaussian Image dealocation: ";
    deallocateMemory(gaussianImage);
    cout << "[INF] Input Image dealocation: ";
    deallocateMemory(inputImage);
    cout << "[OK] Program finished" << endl;
    return 0;
}