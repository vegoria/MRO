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
    makeDifferenceImage(inputImage, differenceImage, width, height);

    cout << "[INF] Difference Image dealocation: " << endl;
    deallocateMemory(differenceImage);
    cout << "[INF] Input Image dealocation: " << endl;
    deallocateMemory(inputImage);
    cout << "[OK] Program finished" << endl;
    return 0;
}