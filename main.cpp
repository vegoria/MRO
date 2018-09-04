#include <iostream>
#include "include/imageManagment.hpp"
#include "include/imageOperations.hpp"
#include "include/watershade.hpp"
#include <memory>
using namespace std;



int main()
{
    int height, width, maxColor, startX, startY, numOfGaussianRepetition;
    int headerPos = readImageHeader(width, height, maxColor);
    double elapsedTime = 0.0;

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

    cout << "[USR] Set number of Gaussian filter repetitions:";
    cin >> numOfGaussianRepetition;
    elapsedTime += makeGaussianFilterSeveralTimes(inputImage,
                                                  width,
                                                  height,
                                                  numOfGaussianRepetition);
    saveImage(inputImage,
              width,
              height,
              FILTERED);

    elapsedTime += makeDifferenceImage(inputImage,
                                       differenceImage,
                                       width,
                                       height);

    elapsedTime += gaussianFilter(differenceImage,
                                  width,
                                  height);
    elapsedTime += makeBright(differenceImage,
                              width,
                              height,
                              10);

    cout << "[USR] Set starting point (x, y):";
    cin >> startX;
    cin >> startY;

    int treshold;
    cout << "[USR] Set treshold:";
    cin >> treshold;

    unique_ptr<Watershade> watershade = make_unique<Watershade>(width, height);
    watershade->setTreshold(treshold);
    watershade->setImage(differenceImage);
    watershade->setStartingPoint(startX, startY);
    elapsedTime += watershade->performWatershade();

    saveImage(differenceImage, width, height, WATERSHED);

    deallocateMemory(differenceImage);
    deallocateMemory(inputImage);

    cout << "[OK] Program finished, total time: " << elapsedTime << endl;
    return 0;
}