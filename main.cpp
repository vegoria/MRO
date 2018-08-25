#include <iostream>
#include "memoryManagment/imageAllocation.hpp"

using namespace std;

int main()
{
    int height, width, maxColor;
    int headerPos = readImageHeader(width, height, maxColor);

    unsigned char **inputImage = new unsigned char* [height];
    inputImage[0] = new unsigned char [height*width];
    for(int i = 1; i < height; i++)
    {
        inputImage[i] = inputImage[i-1] + width;
    }

    readImageData(width, height, maxColor, headerPos, inputImage);
    cout << "[INF] Image size are: " << height << " x " << width << endl;




    deallocateMemory(inputImage);
    cout << "[OK] Program finished" << endl;
    return 0;
}