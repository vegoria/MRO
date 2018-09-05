#include "../include/imageManagment.hpp"
#include "../tgaSrc/TPGM.h"
#include <iostream>
#include <string>
using namespace std;

static const string INPUT_PATH = "../img/inputFiles/01.pgm";


bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

string getImagePath(ImageKind imageKind)
{
    string imagePath = INPUT_PATH;
    switch(imageKind)
    {
        case ORIGINAL:
        {
            break;
        }
        case ERODED:
        {
            replace(imagePath, "inputFiles", "erodedImages");
            break;
        }
        case DILATATED:
        {
            replace(imagePath, "inputFiles", "dilatatedImage");
            break;
        }
        case DIFFERENCE_IMG:
        {
            replace(imagePath, "inputFiles", "differenceImages");
            break;
        }
        case WATERSHED:
        {
            replace(imagePath, "inputFiles", "outputFiles");
            break;
        }
        case FILTERED:
        {
            replace(imagePath, "inputFiles", "filteredImages");
            break;
        }
        default:
        {
            replace(imagePath, "inputFiles", "junk");
        }
    }
    return imagePath;
}

int readImageHeader(int& width, int& height, int& maxColor)
{
    int headerPos;
    if ( (headerPos = readPGMB_header(INPUT_PATH.c_str(), &height, &width, &maxColor)) <= 0 )
    {
        cout << "[ERROR] while reading image header" << endl;
        exit(1);
    }
    return headerPos;
}

void readImageData(int width, int height, int maxColor, int headerPos, unsigned char **image)
{
    if( readPGMB_data(image[0], INPUT_PATH.c_str(), headerPos, height, width, maxColor) == 0 )
    {
        cout << "[ERROR] while reading image data" << endl;
        exit(1);
    }
}
void deallocateMemory(unsigned char** array)
{
    delete[] array[0];
    delete[] array;
}

void saveImage(unsigned char** image, int width, int height, ImageKind imageKind)
{
    string imagePath = getImagePath(imageKind);
    if( writePGMB_image(imagePath.c_str(), image[0], height, width, 255) == 0)
    {
        cout << "[ERROR] Could not save image" << endl;
        exit(1);
    }
}

void saveImageWithPath(unsigned char** image, int width, int height, string path)
{
    string imagePath = path;
    if( writePGMB_image(imagePath.c_str(), image[0], height, width, 255) == 0)
    {
        cout << "[ERROR] Could not save image" << endl;
        exit(1);
    }
}