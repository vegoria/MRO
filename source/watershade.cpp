#include "../include/watershade.hpp"
#include "../tgaSrc/Ttiming.h"
#include <iostream>

using namespace std;

#define WATER_VALUE 128

Watershade::Watershade(int width, int heigth):
    imageWidth(width),
    imageHeight(heigth)
{
    floodedImage = new bool* [imageHeight];
    floodedImage[0] = new bool [imageHeight*imageWidth];
    for(int i = 1; i < imageHeight; i++)
    {
        floodedImage[i] = floodedImage[i-1] + imageWidth;
    }
    for(int i=0; i<imageHeight; i++)
    {
        for(int j=0; j<imageWidth; j++){
            floodedImage[i][j] = false;
    }}
}

Watershade::~Watershade()
{
    delete[] floodedImage[0];
    delete[] floodedImage;
}

void Watershade::setStartingPoint(int x, int y)
{
    startX = x;
    startY = y;
}

void Watershade::setImage(unsigned char** image)
{
    this->image = image;
}

double Watershade::performWatershade()
{
    cout << "[INF] Flooding image... ";
    TTiming tt;
    tt.Begin();
    floodImage();
    markFloodedPixels();
    double elapsedTime = tt.End();
    cout << "elapsed time: " << elapsedTime << endl;
    return elapsedTime;
}

void Watershade::markFloodedPixels()
{
    for(int i=0; i<imageHeight; i++)
    {
        for(int j=0; j<imageWidth; j++)
        {
            if(floodedImage[i][j])
            {
                image[i][j] = WATER_VALUE;
            }
        }
    }
}

void Watershade::floodImage()
{
    floodedImage[startY][startX] = true;
    floodVertical(startX-1, startY);
    floodHorizontal(startX-1, startY);
    for(int i=startY; i<imageHeight-1; i++)
    {
        for(int j=startX; j<imageWidth-1; j++)
        {
            floodVertical(j, i);
            floodHorizontal(j, i);
        }
        for(int j=startX; j>0; j--)
        {
            floodVertical(j, i);
            floodHorizontal(j, i);
        }
    }

    for(int i=startY; i>0; i--)
    {
        for(int j=startX; j<imageWidth-1; j++)
        {
            floodVertical(j, i);
            floodHorizontal(j, i);
        }
        for(int j=startX; j>0; j--)
        {
            floodVertical(j, i);
            floodHorizontal(j, i);
        }
    }
}

bool Watershade::hasFloodedNeighbour(int x, int y)
{
    return floodedImage[y][x-1] or
           floodedImage[y][x+1] or
           floodedImage[y+1][x] or
           floodedImage[y-1][x];
}

void Watershade::floodVertical(int x, int y)
{
    for(int i=y; i>0; i--)
    {
        if(image[i][x] <= treshold and hasFloodedNeighbour(x, i))
        {
            floodedImage[i][x] = true;
        }
        else
        {
            break;
        }
    }
    for(int i=y; i<imageHeight-1; i++)
    {
        if(image[i][x] <= treshold and hasFloodedNeighbour(x, i))
        {
            floodedImage[i][x] = true;
        }
        else
        {
            break;
        }
    }
}

void Watershade::floodHorizontal(int x, int y)
{
    for(int i=x; i>0; i--)
    {
        if(image[y][i] <= treshold and hasFloodedNeighbour(i, y))
        {
            floodedImage[y][i] = true;
        }
        else
        {
            break;
        }
    }
    for(int i=x; i<imageHeight-1; i++)
    {
        if(image[y][i] <= treshold and hasFloodedNeighbour(i, y))
        {
            floodedImage[y][i] = true;
        }
        else
        {
            break;
        }
    }
}

void Watershade::setTreshold(int treshold)
{
    this->treshold = treshold;
}