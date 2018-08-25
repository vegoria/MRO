#include "imageAllocation.hpp"
#include "../tgaSrc/TPGM.h"
#include <iostream>

using namespace std;

static const string INPUT_PATH = "../img/inputFiles/01.pgm";

int readImageHeader(int& width, int& height, int& maxColor)
{
    int headerPos;
    if ( (headerPos = readPGMB_header(INPUT_PATH.c_str(), &height, &width, &maxColor)) <= 0 )
    {
        cout << "[ERROR] while reading image header" << endl;
        exit(1);
    }
    cout << "[OK] Image header read" << endl;
    return headerPos;
}

void readImageData(int width, int height, int maxColor, int headerPos, unsigned char **image)
{
    if( readPGMB_data(image[0], INPUT_PATH.c_str(), headerPos, height, width, maxColor) == 0 )
    {
        cout << "[ERROR] while reading image data" << endl;
        exit(1);
    }
    cout << "[OK] Image data read" << endl;
}
void deallocateMemory(unsigned char** array)
{
    delete[] array[0];
    delete[] array;
    cout << "[OK] Dealocated memory" << endl;
}


